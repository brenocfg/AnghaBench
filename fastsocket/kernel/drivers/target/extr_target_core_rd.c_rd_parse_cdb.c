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
struct se_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  rd_sbc_ops ; 
 int /*<<< orphan*/  sbc_parse_cdb (struct se_cmd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static sense_reason_t
rd_parse_cdb(struct se_cmd *cmd)
{
	return sbc_parse_cdb(cmd, &rd_sbc_ops);
}