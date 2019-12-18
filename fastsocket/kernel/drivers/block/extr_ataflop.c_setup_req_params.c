#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int spt; } ;
struct TYPE_3__ {scalar_t__ errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 scalar_t__ READ ; 
 int ReqBlock ; 
 scalar_t__ ReqBuffer ; 
 scalar_t__ ReqCmd ; 
 int ReqCnt ; 
 scalar_t__ ReqData ; 
 int ReqSector ; 
 int ReqSide ; 
 int ReqTrack ; 
 TYPE_2__* UDT ; 
 scalar_t__ UseTrackbuffer ; 
 TYPE_1__* fd_request ; 
 int read_track ; 

__attribute__((used)) static void setup_req_params( int drive )
{
	int block = ReqBlock + ReqCnt;

	ReqTrack = block / UDT->spt;
	ReqSector = block - ReqTrack * UDT->spt + 1;
	ReqSide = ReqTrack & 1;
	ReqTrack >>= 1;
	ReqData = ReqBuffer + 512 * ReqCnt;

	if (UseTrackbuffer)
		read_track = (ReqCmd == READ && fd_request->errors == 0);
	else
		read_track = 0;

	DPRINT(("Request params: Si=%d Tr=%d Se=%d Data=%08lx\n",ReqSide,
			ReqTrack, ReqSector, (unsigned long)ReqData ));
}