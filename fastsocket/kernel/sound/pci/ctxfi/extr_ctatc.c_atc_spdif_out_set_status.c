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
struct ct_atc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPDIFOO ; 
 int atc_dao_set_status (struct ct_atc*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atc_spdif_out_set_status(struct ct_atc *atc, unsigned int status)
{
	return atc_dao_set_status(atc, status, SPDIFOO);
}