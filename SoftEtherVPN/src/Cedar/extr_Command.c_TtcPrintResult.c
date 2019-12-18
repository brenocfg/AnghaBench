#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str ;
struct TYPE_8__ {int /*<<< orphan*/  (* Write ) (TYPE_2__*,char*) ;} ;
struct TYPE_7__ {int Double; int /*<<< orphan*/  BpsTotal; int /*<<< orphan*/  BpsUpload; int /*<<< orphan*/  BpsDownload; int /*<<< orphan*/  NumBytesTotal; int /*<<< orphan*/  NumBytesUpload; int /*<<< orphan*/  NumBytesDownload; scalar_t__ Raw; int /*<<< orphan*/  Span; } ;
typedef  TYPE_1__ TT_RESULT ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_2__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 int /*<<< orphan*/  GetSpanStrMilli (char*,int,int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReplaceStr (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int /*<<< orphan*/  ToStr3 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToStrByte1000 (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,char*) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*) ; 

void TtcPrintResult(CONSOLE *c, TT_RESULT *res)
{
	CT *ct;
	wchar_t tmp[MAX_SIZE];
	wchar_t tmp1[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	char str[MAX_SIZE];
	// Validate arguments
	if (c == NULL || res == NULL)
	{
		return;
	}

	c->Write(c, _UU("TTC_RES_TITLE"));

	ct = CtNew();
	CtInsertColumn(ct, _UU("TTC_RES_COLUMN_1"), false);
	CtInsertColumn(ct, _UU("TTC_RES_COLUMN_2"), true);
	CtInsertColumn(ct, _UU("TTC_RES_COLUMN_3"), true);

	// Time that was used to measure
	GetSpanStrMilli(str, sizeof(str), res->Span);
	StrToUni(tmp, sizeof(tmp), str);
	CtInsert(ct, _UU("TTC_RES_SPAN"), tmp, L"");

	// Correct the data for Ethernet frame
	CtInsert(ct, _UU("TTC_RES_ETHER"), res->Raw ? _UU("SEC_NO") : _UU("SEC_YES"), L"");

	// Amount of communication data of download direction
	ToStr3(str, sizeof(str), res->NumBytesDownload);
	UniFormat(tmp1, sizeof(tmp1), L"%S Bytes", str);
	ToStrByte1000(str, sizeof(str), res->NumBytesDownload);
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BYTES_DOWNLOAD"), tmp1, tmp2);

	// Amount of communication data of upload direction
	ToStr3(str, sizeof(str), res->NumBytesUpload);
	UniFormat(tmp1, sizeof(tmp1), L"%S Bytes", str);
	ToStrByte1000(str, sizeof(str), res->NumBytesUpload);
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BYTES_UPLOAD"), tmp1, tmp2);

	// Total amount of communication data
	ToStr3(str, sizeof(str), res->NumBytesTotal);
	UniFormat(tmp1, sizeof(tmp1), L"%S Bytes", str);
	ToStrByte1000(str, sizeof(str), res->NumBytesTotal);
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BYTES_TOTAL"), tmp1, tmp2);

	// Calculate the total throughput of input and output of the relay equipment
	CtInsert(ct, _UU("TTC_RES_DOUBLE"), (res->Double == false) ? _UU("SEC_NO") : _UU("SEC_YES"), L"");

	// Average throughput of download direction
	ToStr3(str, sizeof(str), res->BpsDownload);
	UniFormat(tmp1, sizeof(tmp1), L"%S bps", str);
	ToStrByte1000(str, sizeof(str), res->BpsDownload);
	ReplaceStr(str, sizeof(str), str, "Bytes", "bps");
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BPS_DOWNLOAD"), tmp1, tmp2);

	// Average throughput of upload direction
	ToStr3(str, sizeof(str), res->BpsUpload);
	UniFormat(tmp1, sizeof(tmp1), L"%S bps", str);
	ToStrByte1000(str, sizeof(str), res->BpsUpload);
	ReplaceStr(str, sizeof(str), str, "Bytes", "bps");
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BPS_UPLOAD"), tmp1, tmp2);

	// Total average throughput
	ToStr3(str, sizeof(str), res->BpsTotal);
	UniFormat(tmp1, sizeof(tmp1), L"%S bps", str);
	ToStrByte1000(str, sizeof(str), res->BpsTotal);
	ReplaceStr(str, sizeof(str), str, "Bytes", "bps");
	StrToUni(tmp2, sizeof(tmp2), str);
	CtInsert(ct, _UU("TTC_RES_BPS_TOTAL"), tmp1, tmp2);

	CtFree(ct, c);
}