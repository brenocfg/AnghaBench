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
typedef  int /*<<< orphan*/  u8_t ;

/* Variables and functions */
 int bt_mesh_k1 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int bt_mesh_prov_nonce(const u8_t dhkey[32],
                                     const u8_t prov_salt[16],
                                     u8_t nonce[13])
{
    u8_t tmp[16];
    int err;

    err = bt_mesh_k1(dhkey, 32, prov_salt, "prsn", tmp);
    if (!err) {
        memcpy(nonce, tmp + 3, 13);
    }

    return err;
}