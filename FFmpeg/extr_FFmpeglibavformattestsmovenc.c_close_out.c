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

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  av_md5_final (int /*<<< orphan*/ ,int*) ; 
 char* cur_name ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int* hash ; 
 int /*<<< orphan*/  md5 ; 
 int /*<<< orphan*/ * out ; 
 int out_size ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void close_out(void)
{
    int i;
    av_md5_final(md5, hash);
    for (i = 0; i < HASH_SIZE; i++)
        printf("%02x", hash[i]);
    printf(" %d %s\n", out_size, cur_name);
    if (out)
        fclose(out);
    out = NULL;
}