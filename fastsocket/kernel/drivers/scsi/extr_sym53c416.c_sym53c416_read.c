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

/* Variables and functions */
 int EMPTY ; 
 scalar_t__ PIO_FIFO_1 ; 
 scalar_t__ PIO_FIFO_CNT ; 
 scalar_t__ PIO_INT_REG ; 
 int READ_TIMEOUT ; 
 int SCI ; 
 scalar_t__ fastpio ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  insl (scalar_t__,unsigned char*,unsigned int) ; 
 int jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sym53c416_lock ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static __inline__ unsigned int sym53c416_read(int base, unsigned char *buffer, unsigned int len)
{
	unsigned int orig_len = len;
	unsigned long flags = 0;
	unsigned int bytes_left;
	unsigned long i;
	int timeout = READ_TIMEOUT;

	/* Do transfer */
	spin_lock_irqsave(&sym53c416_lock, flags);
	while(len && timeout)
	{
		bytes_left = inb(base + PIO_FIFO_CNT); /* Number of bytes in the PIO FIFO */
		if(fastpio && bytes_left > 3)
		{
			insl(base + PIO_FIFO_1, buffer, bytes_left >> 2);
			buffer += bytes_left & 0xFC;
			len -= bytes_left & 0xFC;
		}
		else if(bytes_left > 0)
		{
			len -= bytes_left;
			for(; bytes_left > 0; bytes_left--)
				*(buffer++) = inb(base + PIO_FIFO_1);
		}
		else
		{
			i = jiffies + timeout;
			spin_unlock_irqrestore(&sym53c416_lock, flags);
			while(time_before(jiffies, i) && (inb(base + PIO_INT_REG) & EMPTY) && timeout)
				if(inb(base + PIO_INT_REG) & SCI)
					timeout = 0;
			spin_lock_irqsave(&sym53c416_lock, flags);
			if(inb(base + PIO_INT_REG) & EMPTY)
				timeout = 0;
		}
	}
	spin_unlock_irqrestore(&sym53c416_lock, flags);
	return orig_len - len;
}