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
typedef  scalar_t__ u16 ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ LOG10_2 ; 
 int LOG2_LOG_TABLE_SIZE ; 
 int* log_table ; 
 int qm_add16 (int,int) ; 
 int qm_add32 (int,int) ; 
 int qm_muls16 (int,int) ; 
 scalar_t__ qm_mulu16 (scalar_t__,scalar_t__) ; 
 int qm_norm32 (int) ; 
 int qm_shl32 (int,int) ; 

void qm_log10(s32 N, s16 qN, s16 *log10N, s16 *qLog10N)
{
	s16 s16norm, s16tableIndex, s16errorApproximation;
	u16 u16offset;
	s32 s32log;

	/* normalize the N. */
	s16norm = qm_norm32(N);
	N = N << s16norm;

	/* The qformat of N after normalization.
	 * -30 is added to treat the no as between 1.0 to 2.0
	 * i.e. after adding the -30 to the qformat the decimal point will be
	 * just rigtht of the MSB. (i.e. after sign bit and 1st MSB). i.e.
	 * at the right side of 30th bit.
	 */
	qN = qN + s16norm - 30;

	/* take the table index as the LOG2_OF_LOG_TABLE_SIZE bits right of the
	 * MSB */
	s16tableIndex = (s16) (N >> (32 - (2 + LOG2_LOG_TABLE_SIZE)));

	/* remove the MSB. the MSB is always 1 after normalization. */
	s16tableIndex =
		s16tableIndex & (s16) ((1 << LOG2_LOG_TABLE_SIZE) - 1);

	/* remove the (1+LOG2_OF_LOG_TABLE_SIZE) MSBs in the N. */
	N = N & ((1 << (32 - (2 + LOG2_LOG_TABLE_SIZE))) - 1);

	/* take the offset as the 16 MSBS after table index.
	 */
	u16offset = (u16) (N >> (32 - (2 + LOG2_LOG_TABLE_SIZE + 16)));

	/* look the log value in the table. */
	s32log = log_table[s16tableIndex];      /* q.15 format */

	/* interpolate using the offset. q.15 format. */
	s16errorApproximation = (s16) qm_mulu16(u16offset,
				(u16) (log_table[s16tableIndex + 1] -
				       log_table[s16tableIndex]));

	 /* q.15 format */
	s32log = qm_add16((s16) s32log, s16errorApproximation);

	/* adjust for the qformat of the N as
	 * log2(mag * 2^x) = log2(mag) + x
	 */
	s32log = qm_add32(s32log, ((s32) -qN) << 15);   /* q.15 format */

	/* normalize the result. */
	s16norm = qm_norm32(s32log);

	/* bring all the important bits into lower 16 bits */
	/* q.15+s16norm-16 format */
	s32log = qm_shl32(s32log, s16norm - 16);

	/* compute the log10(N) by multiplying log2(N) with log10(2).
	 * as log10(mag * 2^x) = log2(mag * 2^x) * log10(2)
	 * log10N in q.15+s16norm-16+1 (LOG10_2 is in q.16)
	 */
	*log10N = qm_muls16((s16) s32log, (s16) LOG10_2);

	/* write the q format of the result. */
	*qLog10N = 15 + s16norm - 16 + 1;

	return;
}