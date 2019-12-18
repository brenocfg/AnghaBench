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
struct kvec {unsigned int iov_len; unsigned char* iov_base; } ;

/* Variables and functions */

__attribute__((used)) static int
smb_move_iov(struct kvec **data, size_t *num, struct kvec *vec, unsigned amount)
{
	struct kvec *iv = *data;
	int i;
	int len;

	/*
	 *	Eat any sent kvecs
	 */
	while (iv->iov_len <= amount) {
		amount -= iv->iov_len;
		iv++;
		(*num)--;
	}

	/*
	 *	And chew down the partial one
	 */
	vec[0].iov_len = iv->iov_len-amount;
	vec[0].iov_base =((unsigned char *)iv->iov_base)+amount;
	iv++;

	len = vec[0].iov_len;

	/*
	 *	And copy any others
	 */
	for (i = 1; i < *num; i++) {
		vec[i] = *iv++;
		len += vec[i].iov_len;
	}

	*data = vec;
	return len;
}