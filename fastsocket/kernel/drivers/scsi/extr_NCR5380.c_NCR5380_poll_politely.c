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
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NCR5380_local_declare () ; 
 int NCR5380_read (int) ; 
 int /*<<< orphan*/  NCR5380_setup (struct Scsi_Host*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int jiffies ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static int NCR5380_poll_politely(struct Scsi_Host *instance, int reg, int bit, int val, int t)
{
	NCR5380_local_declare();
	int n = 500;		/* At about 8uS a cycle for the cpu access */
	unsigned long end = jiffies + t;
	int r;
	
	NCR5380_setup(instance);

	while( n-- > 0)
	{
		r = NCR5380_read(reg);
		if((r & bit) == val)
			return 0;
		cpu_relax();
	}
	
	/* t time yet ? */
	while(time_before(jiffies, end))
	{
		r = NCR5380_read(reg);
		if((r & bit) == val)
			return 0;
		if(!in_interrupt())
			cond_resched();
		else
			cpu_relax();
	}
	return -ETIMEDOUT;
}