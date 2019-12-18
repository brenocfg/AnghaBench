#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum spi_signal_type { ____Placeholder_spi_signal_type } spi_signal_type ;
struct TYPE_3__ {int value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int SPI_SIGNAL_UNKNOWN ; 
 TYPE_1__* signal_types ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline enum spi_signal_type spi_signal_to_value(const char *name)
{
	int i, len;

	for (i = 0; i < ARRAY_SIZE(signal_types); i++) {
		len =  strlen(signal_types[i].name);
		if (strncmp(name, signal_types[i].name, len) == 0 &&
		    (name[len] == '\n' || name[len] == '\0'))
			return signal_types[i].value;
	}
	return SPI_SIGNAL_UNKNOWN;
}