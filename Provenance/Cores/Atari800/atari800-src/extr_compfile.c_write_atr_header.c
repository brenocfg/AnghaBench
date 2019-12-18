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
struct AFILE_ATR_Header {void* hiseccounthi; void* hiseccountlo; void* seccounthi; void* seccountlo; void* secsizehi; void* secsizelo; int /*<<< orphan*/  magic2; int /*<<< orphan*/  magic1; } ;
typedef  int /*<<< orphan*/  header ;
typedef  int ULONG ;
typedef  void* UBYTE ;
struct TYPE_3__ {int sectorcount; int sectorsize; int /*<<< orphan*/  fp; } ;
typedef  TYPE_1__ ATR_Info ;

/* Variables and functions */
 int /*<<< orphan*/  AFILE_ATR_MAGIC1 ; 
 int /*<<< orphan*/  AFILE_ATR_MAGIC2 ; 
 int fsave (struct AFILE_ATR_Header*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct AFILE_ATR_Header*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_atr_header(const ATR_Info *pai)
{
	int sectorcount;
	int sectorsize;
	ULONG paras;
	struct AFILE_ATR_Header header;
	sectorcount = pai->sectorcount;
	sectorsize = pai->sectorsize;
	paras = (sectorsize != 256 || sectorcount <= 3)
		? (sectorcount << 3) /* single density or only boot sectors: sectorcount * 128 / 16 */
		: (sectorcount << 4) - 0x18; /* double density with 128-byte boot sectors: (sectorcount * 256 - 3 * 128) / 16 */
	memset(&header, 0, sizeof(header));
	header.magic1 = AFILE_ATR_MAGIC1;
	header.magic2 = AFILE_ATR_MAGIC2;
	header.secsizelo = (UBYTE) sectorsize;
	header.secsizehi = (UBYTE) (sectorsize >> 8);
	header.seccountlo = (UBYTE) paras;
	header.seccounthi = (UBYTE) (paras >> 8);
	header.hiseccountlo = (UBYTE) (paras >> 16);
	header.hiseccounthi = (UBYTE) (paras >> 24);
	return fsave(&header, sizeof(header), pai->fp);
}