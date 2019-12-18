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
#define  ELFTC_DEM_ARM 130 
#define  ELFTC_DEM_GNU2 129 
#define  ELFTC_DEM_GNU3 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* cpp_demangle_ARM (char const*) ; 
 char* cpp_demangle_gnu2 (char const*) ; 
 char* cpp_demangle_gnu3 (char const*) ; 

__attribute__((used)) static char *
demangle(const char *s, unsigned int style, unsigned int rc)
{

	(void) rc;			/* XXX */
	switch (style) {
	case ELFTC_DEM_ARM: return (cpp_demangle_ARM(s));
	case ELFTC_DEM_GNU2: return (cpp_demangle_gnu2(s));
	case ELFTC_DEM_GNU3: return (cpp_demangle_gnu3(s));
	default:
		assert(0);
		return (NULL);
	}
}