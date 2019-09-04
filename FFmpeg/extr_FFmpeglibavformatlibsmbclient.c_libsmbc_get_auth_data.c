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
typedef  int /*<<< orphan*/  SMBCCTX ;

/* Variables and functions */

__attribute__((used)) static void libsmbc_get_auth_data(SMBCCTX *c, const char *server, const char *share,
                                  char *workgroup, int workgroup_len,
                                  char *username, int username_len,
                                  char *password, int password_len)
{
    /* Do nothing yet. Credentials are passed via url.
     * Callback must exists, there might be a segmentation fault otherwise. */
}