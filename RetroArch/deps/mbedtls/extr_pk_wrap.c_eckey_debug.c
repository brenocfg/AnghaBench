#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/ * value; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ mbedtls_pk_debug_item ;
struct TYPE_5__ {int /*<<< orphan*/  Q; } ;
typedef  TYPE_2__ mbedtls_ecp_keypair ;

/* Variables and functions */
 int /*<<< orphan*/  MBEDTLS_PK_DEBUG_ECP ; 

__attribute__((used)) static void eckey_debug( const void *ctx, mbedtls_pk_debug_item *items )
{
    items->type = MBEDTLS_PK_DEBUG_ECP;
    items->name = "eckey.Q";
    items->value = &( ((mbedtls_ecp_keypair *) ctx)->Q );
}