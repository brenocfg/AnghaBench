#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  u8_t ;
struct mbedtls_ecp_point {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mbedtls_ecp_group ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_ECP_DP_SECP256R1 ; 
 scalar_t__ mbedtls_ecp_check_pubkey (TYPE_1__*,struct mbedtls_ecp_point*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_ecp_group_init (TYPE_1__*) ; 
 scalar_t__ mbedtls_ecp_group_load (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_free (struct mbedtls_ecp_point*) ; 
 int /*<<< orphan*/  mbedtls_ecp_point_init (struct mbedtls_ecp_point*) ; 
 scalar_t__ mbedtls_ecp_point_read_binary (TYPE_1__*,struct mbedtls_ecp_point*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

bool bt_mesh_check_public_key(const u8_t key[64])
{
    struct mbedtls_ecp_point pt = {0};
    mbedtls_ecp_group grp = {0};
    bool rc = false;

    uint8_t pub[65] = {0};
    /* Hardcoded first byte of pub key for MBEDTLS_ECP_PF_UNCOMPRESSED */
    pub[0] = 0x04;
    memcpy(&pub[1], key, 64);

    /* Initialize the required structures here */
    mbedtls_ecp_point_init(&pt);
    mbedtls_ecp_group_init(&grp);

    /* Below 3 steps are to validate public key on curve secp256r1 */
    if (mbedtls_ecp_group_load(&grp, MBEDTLS_ECP_DP_SECP256R1) != 0) {
        goto exit;
    }

    if (mbedtls_ecp_point_read_binary(&grp, &pt, pub, 65) != 0) {
        goto exit;
    }

    if (mbedtls_ecp_check_pubkey(&grp, &pt) != 0) {
        goto exit;
    }

    rc = true;

exit:
    mbedtls_ecp_point_free(&pt);
    mbedtls_ecp_group_free(&grp);
    return rc;

}