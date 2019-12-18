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
struct sas_rphy {int dummy; } ;
struct request_queue {struct sas_rphy* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  rphy_to_shost (struct sas_rphy*) ; 
 int /*<<< orphan*/  sas_smp_request (struct request_queue*,int /*<<< orphan*/ ,struct sas_rphy*) ; 

__attribute__((used)) static void sas_non_host_smp_request(struct request_queue *q)
{
	struct sas_rphy *rphy = q->queuedata;
	sas_smp_request(q, rphy_to_shost(rphy), rphy);
}