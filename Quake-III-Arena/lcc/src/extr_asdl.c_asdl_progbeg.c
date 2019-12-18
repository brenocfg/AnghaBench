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
struct TYPE_3__ {int /*<<< orphan*/  interfaces; int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  Seq_addhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Seq_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Text_box (char*,scalar_t__) ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interfaces ; 
 TYPE_1__* pickle ; 
 TYPE_1__* rcc_program (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  to_generic_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asdl_progbeg(int argc, char *argv[]) {
	int i;

#if WIN32
	_setmode(_fileno(stdout), _O_BINARY);
#endif
	pickle = rcc_program(1, 0, Seq_new(0), Seq_new(0), argc, Seq_new(0));
	for (i = 0; i < argc; i++)
		Seq_addhi(pickle->argv, to_generic_string(Text_box(argv[i], strlen(argv[i]) + 1)));
	interfaces = pickle->interfaces;
}