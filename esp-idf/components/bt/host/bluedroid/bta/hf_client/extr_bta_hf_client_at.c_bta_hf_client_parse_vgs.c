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
 int /*<<< orphan*/  bta_hf_client_handle_vgs ; 
 char* bta_hf_client_parse_uint32 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *bta_hf_client_parse_vgs(char *buffer)
{
    AT_CHECK_EVENT(buffer, "+VGS:");

    return bta_hf_client_parse_uint32(buffer, bta_hf_client_handle_vgs);
}