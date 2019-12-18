#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct blufi_security {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  aes; int /*<<< orphan*/  dhm; struct TYPE_4__* dh_param; } ;

/* Variables and functions */
 TYPE_1__* blufi_sec ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  mbedtls_aes_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbedtls_dhm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

void blufi_security_deinit(void)
{
    if (blufi_sec == NULL) {
        return;
    }
    if (blufi_sec->dh_param){
        free(blufi_sec->dh_param);
        blufi_sec->dh_param = NULL;
    }
    mbedtls_dhm_free(&blufi_sec->dhm);
    mbedtls_aes_free(&blufi_sec->aes);

    memset(blufi_sec, 0x0, sizeof(struct blufi_security));

    free(blufi_sec);
    blufi_sec =  NULL;
}