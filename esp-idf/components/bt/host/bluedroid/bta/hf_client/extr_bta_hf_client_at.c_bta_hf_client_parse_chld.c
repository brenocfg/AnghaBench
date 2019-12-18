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
 int /*<<< orphan*/  AT_CHECK_EVENT (char*,char*) ; 
 int /*<<< orphan*/  AT_CHECK_RN (char*) ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_HOLD_ACC ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_MERGE ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_MERGE_DETACH ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_PRIV_X ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_REL ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_REL_ACC ; 
 int /*<<< orphan*/  BTA_HF_CLIENT_CHLD_REL_X ; 
 int /*<<< orphan*/  bta_hf_client_handle_chld (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static char *bta_hf_client_parse_chld(char *buffer)
{
    AT_CHECK_EVENT(buffer, "+CHLD:");

    if (*buffer != '(') {
        return NULL;
    }

    buffer++;

    while (*buffer != '\0') {
        if (strncmp("0", buffer, 1) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_REL);
            buffer++;
        } else if (strncmp("1x", buffer, 2) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_REL_X);
            buffer += 2;
        } else if (strncmp("1", buffer, 1) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_REL_ACC);
            buffer++;
        } else if (strncmp("2x", buffer, 2) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_PRIV_X);
            buffer += 2;
        } else if (strncmp("2", buffer, 1) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_HOLD_ACC);
            buffer++;
        } else if (strncmp("3", buffer, 1) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_MERGE);
            buffer++;
        } else if (strncmp("4", buffer, 1) == 0) {
            bta_hf_client_handle_chld(BTA_HF_CLIENT_CHLD_MERGE_DETACH);
            buffer++;
        } else {
            return NULL;
        }

        if (*buffer == ',') {
            buffer++;
            continue;
        }

        if (*buffer == ')') {
            buffer++;
            break;
        }

        return NULL;
    }

    AT_CHECK_RN(buffer);

    return buffer;
}