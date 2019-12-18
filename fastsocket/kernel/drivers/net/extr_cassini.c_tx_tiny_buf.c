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
struct cas {void** tx_tiny_bufs; } ;

/* Variables and functions */
 int const TX_TINY_BUF_LEN ; 

__attribute__((used)) static inline void *tx_tiny_buf(struct cas *cp, const int ring,
				const int entry)
{
	return cp->tx_tiny_bufs[ring] + TX_TINY_BUF_LEN*entry;
}