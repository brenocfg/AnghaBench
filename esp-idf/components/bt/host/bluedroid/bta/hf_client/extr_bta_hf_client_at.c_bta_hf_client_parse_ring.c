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
 int /*<<< orphan*/  bta_hf_client_handle_ring () ; 

__attribute__((used)) static char *bta_hf_client_parse_ring(char *buffer)
{
    AT_CHECK_EVENT(buffer, "RING");
    AT_CHECK_RN(buffer);

    bta_hf_client_handle_ring();

    return buffer;
}