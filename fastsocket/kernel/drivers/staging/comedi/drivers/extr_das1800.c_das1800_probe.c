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
struct das1800_board {int name; } ;
struct comedi_device {scalar_t__ board_ptr; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS1800_DIGITAL ; 
 int das1701ao ; 
 int das1701st ; 
 int das1701st_da ; 
 int das1702ao ; 
 int das1702hr ; 
 int das1702hr_da ; 
 int das1702st ; 
 int das1702st_da ; 
 struct das1800_board* das1800_boards ; 
 int das1801ao ; 
 int das1801hc ; 
 int das1801st ; 
 int das1801st_da ; 
 int das1802ao ; 
 int das1802hc ; 
 int das1802hr ; 
 int das1802hr_da ; 
 int das1802st ; 
 int das1802st_da ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int das1800_probe(struct comedi_device *dev)
{
	int id;
	int board;

	id = (inb(dev->iobase + DAS1800_DIGITAL) >> 4) & 0xf;	/* get id bits */
	board = ((struct das1800_board *)dev->board_ptr) - das1800_boards;

	switch (id) {
	case 0x3:
		if (board == das1801st_da || board == das1802st_da ||
		    board == das1701st_da || board == das1702st_da) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk
		    (" Board model (probed, not recommended): das-1800st-da series\n");
		return das1801st;
		break;
	case 0x4:
		if (board == das1802hr_da || board == das1702hr_da) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk
		    (" Board model (probed, not recommended): das-1802hr-da\n");
		return das1802hr;
		break;
	case 0x5:
		if (board == das1801ao || board == das1802ao ||
		    board == das1701ao || board == das1702ao) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk
		    (" Board model (probed, not recommended): das-1800ao series\n");
		return das1801ao;
		break;
	case 0x6:
		if (board == das1802hr || board == das1702hr) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk(" Board model (probed, not recommended): das-1802hr\n");
		return das1802hr;
		break;
	case 0x7:
		if (board == das1801st || board == das1802st ||
		    board == das1701st || board == das1702st) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk
		    (" Board model (probed, not recommended): das-1800st series\n");
		return das1801st;
		break;
	case 0x8:
		if (board == das1801hc || board == das1802hc) {
			printk(" Board model: %s\n",
			       das1800_boards[board].name);
			return board;
		}
		printk
		    (" Board model (probed, not recommended): das-1800hc series\n");
		return das1801hc;
		break;
	default:
		printk
		    (" Board model: probe returned 0x%x (unknown, please report)\n",
		     id);
		return board;
		break;
	}
	return -1;
}