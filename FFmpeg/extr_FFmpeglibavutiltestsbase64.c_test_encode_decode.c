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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int MAX_DATA_SIZE ; 
 int MAX_ENCODED_SIZE ; 
 int av_base64_decode (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  av_base64_encode (char*,int,int /*<<< orphan*/  const*,unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int test_encode_decode(const uint8_t *data, unsigned int data_size,
                              const char *encoded_ref)
{
    char  encoded[MAX_ENCODED_SIZE];
    uint8_t data2[MAX_DATA_SIZE];
    int data2_size, max_data2_size = MAX_DATA_SIZE;

    if (!av_base64_encode(encoded, MAX_ENCODED_SIZE, data, data_size)) {
        printf("Failed: cannot encode the input data\n");
        return 1;
    }
    if (encoded_ref && strcmp(encoded, encoded_ref)) {
        printf("Failed: encoded string differs from reference\n"
               "Encoded:\n%s\nReference:\n%s\n", encoded, encoded_ref);
        return 1;
    }

    if ((data2_size = av_base64_decode(data2, encoded, max_data2_size)) != data_size) {
        printf("Failed: cannot decode the encoded string\n"
               "Encoded:\n%s\n", encoded);
        return 1;
    }
    if ((data2_size = av_base64_decode(data2, encoded, data_size)) != data_size) {
        printf("Failed: cannot decode with minimal buffer\n"
               "Encoded:\n%s\n", encoded);
        return 1;
    }
    if (memcmp(data2, data, data_size)) {
        printf("Failed: encoded/decoded data differs from original data\n");
        return 1;
    }
    if (av_base64_decode(NULL, encoded, 0) != 0) {
        printf("Failed: decode to NULL buffer\n");
        return 1;
    }
    if (strlen(encoded)) {
        char *end = strchr(encoded, '=');
        if (!end)
            end = encoded + strlen(encoded) - 1;
        *end = '%';
        if (av_base64_decode(NULL, encoded, 0) >= 0) {
            printf("Failed: error detection\n");
            return 1;
        }
    }

    printf("Passed!\n");
    return 0;
}