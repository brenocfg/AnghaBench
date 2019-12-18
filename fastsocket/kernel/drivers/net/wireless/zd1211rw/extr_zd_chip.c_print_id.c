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
struct zd_chip {int dummy; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  scnprint_id (struct zd_chip*,char*,int) ; 
 int /*<<< orphan*/  zd_chip_dev (struct zd_chip*) ; 

__attribute__((used)) static void print_id(struct zd_chip *chip)
{
	char buffer[80];

	scnprint_id(chip, buffer, sizeof(buffer));
	buffer[sizeof(buffer)-1] = 0;
	dev_info(zd_chip_dev(chip), "%s\n", buffer);
}