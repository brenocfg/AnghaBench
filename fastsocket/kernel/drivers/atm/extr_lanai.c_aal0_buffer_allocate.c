#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * start; } ;
struct lanai_dev {TYPE_1__ aal0buf; int /*<<< orphan*/  pci; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAL0_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  lanai_buf_allocate (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int aal0_buffer_allocate(struct lanai_dev *lanai)
{
	DPRINTK("aal0_buffer_allocate: allocating AAL0 RX buffer\n");
	lanai_buf_allocate(&lanai->aal0buf, AAL0_RX_BUFFER_SIZE, 80,
			   lanai->pci);
	return (lanai->aal0buf.start == NULL) ? -ENOMEM : 0;
}