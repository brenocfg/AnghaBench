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
typedef  int /*<<< orphan*/  name_src ;
typedef  int /*<<< orphan*/  name_dst ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ASSERT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void test_spiffs_rename(const char* filename_prefix)
{
    char name_dst[64];
    char name_src[64];
    snprintf(name_dst, sizeof(name_dst), "%s_dst.txt", filename_prefix);
    snprintf(name_src, sizeof(name_src), "%s_src.txt", filename_prefix);

    unlink(name_dst);
    unlink(name_src);

    FILE* f = fopen(name_src, "w+");
    TEST_ASSERT_NOT_NULL(f);
    const char* str = "0123456789";
    for (int i = 0; i < 400; ++i) {
        TEST_ASSERT_NOT_EQUAL(EOF, fputs(str, f));
    }
    TEST_ASSERT_EQUAL(0, fclose(f));
    TEST_ASSERT_EQUAL(0, rename(name_src, name_dst));
    TEST_ASSERT_NULL(fopen(name_src, "r"));
    FILE* fdst = fopen(name_dst, "r");
    TEST_ASSERT_NOT_NULL(fdst);
    TEST_ASSERT_EQUAL(0, fseek(fdst, 0, SEEK_END));
    TEST_ASSERT_EQUAL(4000, ftell(fdst));
    TEST_ASSERT_EQUAL(0, fclose(fdst));
}