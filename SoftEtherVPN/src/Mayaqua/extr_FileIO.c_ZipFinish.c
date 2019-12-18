#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  e ;
typedef  int /*<<< orphan*/  dh ;
typedef  int /*<<< orphan*/  d ;
struct TYPE_16__ {TYPE_6__* Fifo; int /*<<< orphan*/  FileList; } ;
typedef  TYPE_1__ ZIP_PACKER ;
struct TYPE_17__ {scalar_t__ HeaderPos; TYPE_3__* Name; scalar_t__ Attributes; } ;
typedef  TYPE_2__ ZIP_FILE ;
struct TYPE_18__ {scalar_t__ CommentLen; void* StartPos; void* DirSize; void* DirEntry; void* DiskDirEntry; scalar_t__ StartDiskNum; scalar_t__ DiskNum; void* Signature; void* HeaderPos; void* OutAttr; scalar_t__ InAttr; int /*<<< orphan*/  ExtraLen; int /*<<< orphan*/  FileNameLen; int /*<<< orphan*/  UncompSize; int /*<<< orphan*/  CompSize; int /*<<< orphan*/  Crc32; int /*<<< orphan*/  FileDate; int /*<<< orphan*/  FileTime; int /*<<< orphan*/  CompType; int /*<<< orphan*/  Option; int /*<<< orphan*/  NeedVer; void* MadeVer; } ;
typedef  TYPE_3__ ZIP_END_HEADER ;
typedef  TYPE_3__ ZIP_DIR_HEADER ;
typedef  TYPE_3__ ZIP_DATA_HEADER ;
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {scalar_t__ total_write_size; } ;
typedef  TYPE_6__ FIFO ;

/* Variables and functions */
 void* Endian16 (int /*<<< orphan*/ ) ; 
 void* Endian32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int StrLen (TYPE_3__*) ; 
 int /*<<< orphan*/  Swap16 (scalar_t__) ; 
 int /*<<< orphan*/  Swap32 (scalar_t__) ; 
 int /*<<< orphan*/  WriteFifo (TYPE_6__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  WriteZipDataHeader (TYPE_2__*,TYPE_3__*,int) ; 
 scalar_t__ ZIP_SIGNATURE_END ; 
 scalar_t__ ZIP_VERSION ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

FIFO *ZipFinish(ZIP_PACKER *p)
{
	UINT i;
	UINT pos_start;
	UINT pos_end;
	ZIP_END_HEADER e;
	// Validate arguments
	if (p == NULL)
	{
		return NULL;
	}

	pos_start = (UINT)p->Fifo->total_write_size;

	for (i = 0;i < LIST_NUM(p->FileList);i++)
	{
		ZIP_FILE *f = LIST_DATA(p->FileList, i);
		ZIP_DIR_HEADER d;
		ZIP_DATA_HEADER dh;

		Zero(&d, sizeof(d));
		Zero(&dh, sizeof(dh));

		d.Signature = Endian32(Swap32(0x02014B50));
		d.MadeVer = Endian16(Swap16(ZIP_VERSION));

		WriteZipDataHeader(f, &dh, true);

		d.NeedVer = dh.NeedVer;
		d.Option = dh.Option;
		d.CompType = dh.CompType;
		d.FileTime = dh.FileTime;
		d.FileDate = dh.FileDate;
		d.Crc32 = dh.Crc32;
		d.CompSize = dh.CompSize;
		d.UncompSize = dh.UncompSize;
		d.FileNameLen = dh.FileNameLen;
		d.ExtraLen = dh.ExtraLen;
		d.CommentLen = 0;
		d.DiskNum = 0;
		d.InAttr = 0;
		d.OutAttr = Endian32(Swap32((USHORT)f->Attributes));
		d.HeaderPos = Endian32(Swap32(f->HeaderPos));

		WriteFifo(p->Fifo, &d, sizeof(d));
		WriteFifo(p->Fifo, f->Name, StrLen(f->Name));
	}

	pos_end = (UINT)p->Fifo->total_write_size;

	Zero(&e, sizeof(e));
	e.Signature = Endian32(Swap32(ZIP_SIGNATURE_END));
	e.DiskNum = e.StartDiskNum = 0;
	e.DiskDirEntry = e.DirEntry = Endian16(Swap16((USHORT)LIST_NUM(p->FileList)));
	e.DirSize = Endian32(Swap32((UINT)(pos_end - pos_start)));
	e.StartPos = Endian32(Swap32(pos_start));
	e.CommentLen = 0;

	WriteFifo(p->Fifo, &e, sizeof(e));

	return p->Fifo;
}