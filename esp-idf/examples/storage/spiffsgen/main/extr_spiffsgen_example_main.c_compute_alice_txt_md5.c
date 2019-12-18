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
typedef  int /*<<< orphan*/  mbedtls_md5_context ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int MD5_MAX_LEN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 size_t fread (void*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_finish_ret (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  mbedtls_md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_starts_ret (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_md5_update_ret (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static void compute_alice_txt_md5(void)
{
    ESP_LOGI(TAG, "Computing alice.txt MD5 hash");

    // The file alice.txt lives under a subdirectory, though SPIFFS itself is flat
    FILE* f = fopen("/spiffs/sub/alice.txt", "r");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open alice.txt");
        return;
    }

    // Read file and compute the digest chunk by chunk
    #define MD5_MAX_LEN 16

    char buf[64];
    mbedtls_md5_context ctx;
    unsigned char digest[MD5_MAX_LEN];

    mbedtls_md5_init(&ctx);
    mbedtls_md5_starts_ret(&ctx);

    size_t read;

    do {
        read = fread((void*) buf, 1, sizeof(buf), f);
        mbedtls_md5_update_ret(&ctx, (unsigned const char*) buf, read);
    } while(read == sizeof(buf));

    mbedtls_md5_finish_ret(&ctx, digest);

    // Create a string of the digest
    char digest_str[MD5_MAX_LEN * 2];

    for (int i = 0; i < MD5_MAX_LEN; i++) {
        sprintf(&digest_str[i * 2], "%02x", (unsigned int)digest[i]);
    }

    // For reference, MD5 should be deeb71f585cbb3ae5f7976d5127faf2a
    ESP_LOGI(TAG, "Computed MD5 hash of alice.txt: %s", digest_str);

    fclose(f);
}