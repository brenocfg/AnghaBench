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
typedef  char const u8_t ;

/* Variables and functions */
 int bt_mesh_aes_cmac_one (char const*,char const*,size_t,char const*) ; 
 size_t strlen (char const*) ; 

int bt_mesh_k1(const u8_t *ikm, size_t ikm_len, const u8_t salt[16],
               const char *info, u8_t okm[16])
{
    int err;

    err = bt_mesh_aes_cmac_one(salt, ikm, ikm_len, okm);
    if (err < 0) {
        return err;
    }

    return bt_mesh_aes_cmac_one(okm, info, strlen(info), okm);
}