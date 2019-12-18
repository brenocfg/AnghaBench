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
struct beiscsi_hba {scalar_t__ fw_timeout; scalar_t__ ue_detected; } ;

/* Variables and functions */

__attribute__((used)) static inline bool beiscsi_error(struct beiscsi_hba *phba)
{
	return phba->ue_detected || phba->fw_timeout;
}