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
struct scc_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCC_ACCESS_INIT (struct scc_port*) ; 
 int SCCread (int /*<<< orphan*/ ) ; 
 int SCSR_ALL_SENT ; 
 int /*<<< orphan*/  SPCOND_STATUS_REG ; 

__attribute__((used)) static int scc_chars_in_buffer (void *ptr)
{
	struct scc_port *port = ptr;
	SCC_ACCESS_INIT(port);

	return (SCCread (SPCOND_STATUS_REG) & SCSR_ALL_SENT) ? 0  : 1;
}