#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
typedef  TYPE_3__* i2eBordStrPtr ;
struct TYPE_5__ {int porID; } ;
struct TYPE_6__ {TYPE_1__ e; } ;
struct TYPE_7__ {int* i2eChannelMap; int /*<<< orphan*/  i2eDataWidth16; TYPE_2__ i2ePom; } ;

/* Variables and functions */
 int ABS_BIGGEST_BOX ; 
 int ABS_MAX_BOXES ; 
 int /*<<< orphan*/  IP2_CALLOUT_MAJOR ; 
 int /*<<< orphan*/  IP2_IPL_MAJOR ; 
 int IP2_MAX_BOARDS ; 
 int /*<<< orphan*/  IP2_TTY_MAJOR ; 
#define  POR_ID_FIIEX 131 
#define  POR_ID_II_4 130 
#define  POR_ID_II_8 129 
#define  POR_ID_II_8R 128 
 int POR_ID_RESERVED ; 
 TYPE_3__** i2BoardPtrTable ; 
 int /*<<< orphan*/  pcVersion ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int ip2_proc_show(struct seq_file *m, void *v)
{
	int	i, j, box;
	int	boxes = 0;
	int	ports = 0;
	int	tports = 0;
	i2eBordStrPtr  pB;
	char *sep;

	seq_printf(m, "ip2info: 1.0 driver: %s\n", pcVersion);
	seq_printf(m, "Driver: SMajor=%d CMajor=%d IMajor=%d MaxBoards=%d MaxBoxes=%d MaxPorts=%d\n",
			IP2_TTY_MAJOR, IP2_CALLOUT_MAJOR, IP2_IPL_MAJOR,
			IP2_MAX_BOARDS, ABS_MAX_BOXES, ABS_BIGGEST_BOX);

	for( i = 0; i < IP2_MAX_BOARDS; ++i ) {
		/* This need to be reset for a board by board count... */
		boxes = 0;
		pB = i2BoardPtrTable[i];
		if( pB ) {
			switch( pB->i2ePom.e.porID & ~POR_ID_RESERVED ) 
			{
			case POR_ID_FIIEX:
				seq_printf(m, "Board %d: EX ports=", i);
				sep = "";
				for( box = 0; box < ABS_MAX_BOXES; ++box )
				{
					ports = 0;

					if( pB->i2eChannelMap[box] != 0 ) ++boxes;
					for( j = 0; j < ABS_BIGGEST_BOX; ++j ) 
					{
						if( pB->i2eChannelMap[box] & 1<< j ) {
							++ports;
						}
					}
					seq_printf(m, "%s%d", sep, ports);
					sep = ",";
					tports += ports;
				}
				seq_printf(m, " boxes=%d width=%d", boxes, pB->i2eDataWidth16 ? 16 : 8);
				break;

			case POR_ID_II_4:
				seq_printf(m, "Board %d: ISA-4 ports=4 boxes=1", i);
				tports = ports = 4;
				break;

			case POR_ID_II_8:
				seq_printf(m, "Board %d: ISA-8-std ports=8 boxes=1", i);
				tports = ports = 8;
				break;

			case POR_ID_II_8R:
				seq_printf(m, "Board %d: ISA-8-RJ11 ports=8 boxes=1", i);
				tports = ports = 8;
				break;

			default:
				seq_printf(m, "Board %d: unknown", i);
				/* Don't try and probe for minor numbers */
				tports = ports = 0;
			}

		} else {
			/* Don't try and probe for minor numbers */
			seq_printf(m, "Board %d: vacant", i);
			tports = ports = 0;
		}

		if( tports ) {
			seq_puts(m, " minors=");
			sep = "";
			for ( box = 0; box < ABS_MAX_BOXES; ++box )
			{
				for ( j = 0; j < ABS_BIGGEST_BOX; ++j )
				{
					if ( pB->i2eChannelMap[box] & (1 << j) )
					{
						seq_printf(m, "%s%d", sep,
							j + ABS_BIGGEST_BOX *
							(box+i*ABS_MAX_BOXES));
						sep = ",";
					}
				}
			}
		}
		seq_putc(m, '\n');
	}
	return 0;
 }