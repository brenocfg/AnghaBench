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
typedef  int /*<<< orphan*/  const u64 ;

/* Variables and functions */
 scalar_t__ after48 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline u64 max48(const u64 seq1, const u64 seq2)
{
	return after48(seq1, seq2) ? seq1 : seq2;
}