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
typedef  int /*<<< orphan*/  BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  NO_OPCODE_CHECKING ; 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_command_complete_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_generic_command_complete(BT_HDR *response)
{
    read_command_complete_header(response, NO_OPCODE_CHECKING, 0 /* bytes after */);

    osi_free(response);
}