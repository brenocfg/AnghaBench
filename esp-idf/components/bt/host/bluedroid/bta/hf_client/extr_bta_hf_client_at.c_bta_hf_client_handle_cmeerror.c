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
typedef  int /*<<< orphan*/  UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_AT_RESULT_CME ; 
 int /*<<< orphan*/  bta_hf_client_handle_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bta_hf_client_handle_cmeerror(UINT32 code)
{
    bta_hf_client_handle_error(BTA_HF_CLIENT_AT_RESULT_CME, code);
}