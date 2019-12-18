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
struct TYPE_3__ {int /*<<< orphan*/  FileNames; scalar_t__ FileNameOffsets; scalar_t__ FileIndexToFolderIndexMap; scalar_t__ FolderStartFileIndex; scalar_t__ PackStreamStartPositions; scalar_t__ FolderStartPackStreamIndex; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ CSzArEx ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SzAr_Init (int /*<<< orphan*/ *) ; 

void SzArEx_Init(CSzArEx *p)
{
   SzAr_Init(&p->db);
   p->FolderStartPackStreamIndex = 0;
   p->PackStreamStartPositions = 0;
   p->FolderStartFileIndex = 0;
   p->FileIndexToFolderIndexMap = 0;
   p->FileNameOffsets = 0;
   Buf_Init(&p->FileNames);
}