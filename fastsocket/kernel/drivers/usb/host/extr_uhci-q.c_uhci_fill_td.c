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
typedef  int /*<<< orphan*/  u32 ;
struct uhci_td {void* buffer; void* token; void* status; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uhci_fill_td(struct uhci_td *td, u32 status,
		u32 token, u32 buffer)
{
	td->status = cpu_to_le32(status);
	td->token = cpu_to_le32(token);
	td->buffer = cpu_to_le32(buffer);
}