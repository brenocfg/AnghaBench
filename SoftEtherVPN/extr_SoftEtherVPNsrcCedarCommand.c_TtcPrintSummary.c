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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/  Print; int /*<<< orphan*/  Param; scalar_t__ Double; scalar_t__ Raw; scalar_t__ Span; int /*<<< orphan*/  Type; int /*<<< orphan*/  NumTcp; int /*<<< orphan*/  Port; int /*<<< orphan*/  Host; } ;
typedef  TYPE_1__ TTC ;

/* Variables and functions */
 char* GetTtcTypeStr (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TtPrint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UniFormat (char*,int,char*,...) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 char* _UU (char*) ; 

void TtcPrintSummary(TTC *ttc)
{
	wchar_t tmp[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	wchar_t *tag = L"%-35s %s";
	// Validate arguments
	if (ttc == NULL)
	{
		return;
	}

	TtPrint(ttc->Param, ttc->Print, L"");
	TtPrint(ttc->Param, ttc->Print, _UU("TTC_SUMMARY_BAR"));
	TtPrint(ttc->Param, ttc->Print, _UU("TTC_SUMMARY_TITLE"));
	TtPrint(ttc->Param, ttc->Print, L"");

	// Destination host name
	StrToUni(tmp2, sizeof(tmp2), ttc->Host);
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_HOST"), tmp2);
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Destination TCP port number
	UniToStru(tmp2, ttc->Port);
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_PORT"), tmp2);
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Number of TCP connections to establish
	UniToStru(tmp2, ttc->NumTcp);
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_NUMTCP"), tmp2);
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Data transmission direction
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_TYPE"), GetTtcTypeStr(ttc->Type));
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Data transmission span
	UniFormat(tmp2, sizeof(tmp2), _UU("TTC_SPAN_STR"), (double)(ttc->Span) / 1000.0);
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_SPAN"), tmp2);
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Correct the data for Ethernet frame
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_ETHER"), ttc->Raw ? _UU("SEC_NO") : _UU("SEC_YES"));
	TtPrint(ttc->Param, ttc->Print, tmp);

	// Measure the total amount of input and output throughput of relay equipment
	UniFormat(tmp, sizeof(tmp), tag, _UU("TTC_SUMMARY_DOUBLE"), ttc->Double ? _UU("SEC_YES") : _UU("SEC_NO"));
	TtPrint(ttc->Param, ttc->Print, tmp);

	TtPrint(ttc->Param, ttc->Print, _UU("TTC_SUMMARY_BAR"));
	TtPrint(ttc->Param, ttc->Print, L"");
}