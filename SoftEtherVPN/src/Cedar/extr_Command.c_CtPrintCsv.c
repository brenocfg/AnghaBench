#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  fmtbuf ;
typedef  int /*<<< orphan*/  buf ;
typedef  int UINT ;
struct TYPE_12__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  Rows; int /*<<< orphan*/  Columns; } ;
struct TYPE_10__ {int /*<<< orphan*/  String; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Strings; } ;
typedef  TYPE_1__ CTR ;
typedef  TYPE_2__ CTC ;
typedef  TYPE_3__ CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CtEscapeCsv (char*,int,int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniStrCat (char*,int,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char*) ; 

void CtPrintCsv(CT *ct, CONSOLE *c)
{
	UINT i, j;
	UINT num_columns = LIST_NUM(ct->Columns);
	wchar_t buf[MAX_SIZE*4];
	wchar_t fmtbuf[MAX_SIZE*4];

	// Show the heading row
	buf[0] = 0;
	for(i=0; i<num_columns; i++)
	{
		CTC *ctc = LIST_DATA(ct->Columns, i);
		CtEscapeCsv(fmtbuf, sizeof(fmtbuf), ctc->String);
		UniStrCat(buf, sizeof(buf), fmtbuf);
		if(i != num_columns-1)
			UniStrCat(buf, sizeof(buf), L",");
	}
	c->Write(c, buf);

	// Show the table body
	for(j=0; j<LIST_NUM(ct->Rows); j++)
	{
		CTR *ctr = LIST_DATA(ct->Rows, j);
		buf[0] = 0;
		for(i=0; i<num_columns; i++)
		{
			CtEscapeCsv(fmtbuf, sizeof(fmtbuf), ctr->Strings[i]);
			UniStrCat(buf, sizeof(buf), fmtbuf);
			if(i != num_columns-1)
				UniStrCat(buf, sizeof(buf), L",");
		}
		c->Write(c, buf);
	}
}