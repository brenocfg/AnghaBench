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
struct s_write {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_command (int,int,struct s_write*) ; 

__attribute__((used)) static void handle_end_of_data(struct s_write *wb)
{
    // We issue a EraseDisplayedMemory here so if there's any captions pending
    // they get written to file.
    handle_command (0x14, 0x2c, wb); // EDM
}