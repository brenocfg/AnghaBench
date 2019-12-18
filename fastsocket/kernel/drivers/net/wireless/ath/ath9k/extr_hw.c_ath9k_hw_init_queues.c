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
struct ath_hw {scalar_t__ intr_txqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DQCUMASK (int) ; 
 int AR_NUM_DCU ; 
 int ATH9K_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_resettxqueue (struct ath_hw*,int) ; 

__attribute__((used)) static void ath9k_hw_init_queues(struct ath_hw *ah)
{
	int i;

	ENABLE_REGWRITE_BUFFER(ah);

	for (i = 0; i < AR_NUM_DCU; i++)
		REG_WRITE(ah, AR_DQCUMASK(i), 1 << i);

	REGWRITE_BUFFER_FLUSH(ah);

	ah->intr_txqs = 0;
	for (i = 0; i < ATH9K_NUM_TX_QUEUES; i++)
		ath9k_hw_resettxqueue(ah, i);
}