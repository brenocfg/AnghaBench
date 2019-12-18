#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  G_FILE_TEST_IS_REGULAR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  appimage_get_elf_section_offset_and_length (char const*,char const*,unsigned long*,unsigned long*) ; 
 char* appimage_hexlify (char*,int const) ; 
 int /*<<< orphan*/  appimage_type2_digest_md5 (char const*,char*) ; 
 scalar_t__ compare_byte_buffers (char*,char*,int const) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int const fread (char*,int,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_file_test (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <my.AppImage>\n", argv[0]);
        printf("\n");
        printf("Calculate AppImage MD5 digest, and compare it to embedded value (if available)\n");
    }

    const char* fname = argv[1];
    if (!g_file_test(fname, G_FILE_TEST_IS_REGULAR)) {
        fprintf(stderr, "No such file or directory: %s\n", fname);
        return 1;
    }

    static const int digest_size = 16;

    // first, calculate MD5 digest using algorithm in libappimage
    char expected_digest[digest_size];

    if (!appimage_type2_digest_md5(fname, expected_digest)) {
        fprintf(stderr, "Could not calculate MD5 digest\n");
        return 1;
    }

    // print hex encoded digest
    char* hexlified_expected_digest = appimage_hexlify(expected_digest, digest_size);
    printf("calculated: %s\n", hexlified_expected_digest);
    free(hexlified_expected_digest);

    unsigned long offset = 0, length = 0;

    static const char section_name[] = ".digest_md5";

    if (!appimage_get_elf_section_offset_and_length(fname, section_name, &offset, &length) || offset == 0 || length == 0) {
        fprintf(stderr, "Could not find %s section in file\n", section_name);
        return 1;
    }

    if (length < digest_size) {
        fprintf(stderr,
            "Invalid section length for section %s: expected %d bytes, found %lu bytes\n",
            section_name, digest_size, length
        );
        return 1;
    }

    char embedded_digest[digest_size];
    FILE* fp = fopen(fname, "r");

    if (fp == NULL) {
        fprintf(stderr, "Failed to open AppImage for writing");
        return 1;
    }

    if (fseek(fp, offset, SEEK_SET) != 0) {
        fprintf(stderr, "Failed to read embedded digest: failed to seek to offset\n");
        fclose(fp);
        return 1;
    }

    if (fread(embedded_digest, sizeof(char), digest_size, fp) != digest_size) {
        fprintf(stderr, "Failed to read embedded digest: read invalid amount of bytes from file\n");
        fclose(fp);
        return 1;
    }

    fclose(fp);

    char* hexlified_embedded_digest = appimage_hexlify(embedded_digest, digest_size);
    printf("  embedded: %s\n", hexlified_embedded_digest);
    free(hexlified_embedded_digest);

    if (compare_byte_buffers(expected_digest, embedded_digest, digest_size)) {
        printf("Digests match\n");
        return 0;
    } else {
        printf("Digests don't match!");
        return 1;
    }
}