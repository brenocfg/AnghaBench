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
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int AV_HASH_MAX_SIZE ; 
 int /*<<< orphan*/  av_hash_final_b64 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  av_hash_final_hex (int /*<<< orphan*/ ,char*,int) ; 
 char* av_hash_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash ; 
 scalar_t__ out_b64 ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void finish(void)
{
    char res[2 * AV_HASH_MAX_SIZE + 4];

    printf("%s=", av_hash_get_name(hash));
    if (out_b64) {
        av_hash_final_b64(hash, res, sizeof(res));
        printf("b64:%s", res);
    } else {
        av_hash_final_hex(hash, res, sizeof(res));
        printf("0x%s", res);
    }
}