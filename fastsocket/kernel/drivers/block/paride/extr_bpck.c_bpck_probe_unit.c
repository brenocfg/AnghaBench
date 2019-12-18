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
struct TYPE_3__ {int unit; } ;
typedef  TYPE_1__ PIA ;

/* Variables and functions */
 int r0 () ; 
 int r1 () ; 
 int /*<<< orphan*/  r2 () ; 
 int /*<<< orphan*/  t2 (int) ; 
 int /*<<< orphan*/  w0 (int) ; 
 int /*<<< orphan*/  w2 (int) ; 

__attribute__((used)) static int bpck_probe_unit ( PIA *pi )

{	int o1, o0, f7, id;
	int t, s;

	id = pi->unit;
	s = 0;
	w2(4); w2(0xe); r2(); t2(2); 
	o1 = r1()&0xf8;
	o0 = r0();
	w0(255-id); w2(4); w0(id);
	t2(8); t2(8); t2(8);
	t2(2); t = r1()&0xf8;
	f7 = ((id % 8) == 7);
	if ((f7) || (t != o1)) { t2(2); s = r1()&0xf8; }
	if ((t == o1) && ((!f7) || (s == o1)))  {
		w2(0x4c); w0(o0);
		return 0;	
	}
	t2(8); w0(0); t2(2); w2(0x4c); w0(o0);
	return 1;
}