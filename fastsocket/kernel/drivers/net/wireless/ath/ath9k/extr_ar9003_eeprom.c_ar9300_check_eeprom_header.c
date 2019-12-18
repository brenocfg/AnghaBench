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
typedef  int /*<<< orphan*/  u8 ;
struct ath_hw {int dummy; } ;
typedef  int /*<<< orphan*/  (* eeprom_read_op ) (struct ath_hw*,int,int /*<<< orphan*/ *,int) ;

/* Variables and functions */
 int ar9300_check_header (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ar9300_check_eeprom_header(struct ath_hw *ah, eeprom_read_op read,
				       int base_addr)
{
	u8 header[4];

	if (!read(ah, base_addr, header, 4))
		return false;

	return ar9300_check_header(header);
}