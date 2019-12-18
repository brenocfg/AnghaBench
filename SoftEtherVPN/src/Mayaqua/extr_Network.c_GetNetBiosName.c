#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int* Query; void* NumQuestions; void* TransactionId; } ;
struct TYPE_5__ {int TransactionId; scalar_t__ Flags; scalar_t__ NumQuestions; int AnswerRRs; int* Response; } ;
typedef  int /*<<< orphan*/  SOCKSET ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  TYPE_1__ NBTRESPONSE ;
typedef  TYPE_2__ NBTREQUEST ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddSockSet (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* Endian16 (int) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitSockSet (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int NUM_NBT_QUERYS_SEND ; 
 int /*<<< orphan*/ * NewUDP (int /*<<< orphan*/ ) ; 
 scalar_t__ Rand16 () ; 
 int RecvFrom (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int SOCK_LATER ; 
 int /*<<< orphan*/  Select (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SendTo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  SleepThread (int) ; 
 scalar_t__ StrCheckLen (char*,int) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ TIMEOUT_NETBIOS_HOSTNAME ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool GetNetBiosName(char *name, UINT size, IP *ip)
{
	SOCK *s;
	UINT i, j;
	bool flag = false;
	bool ok = false;
	NBTREQUEST req;
	UCHAR buf[1024];
	USHORT tran_id[NUM_NBT_QUERYS_SEND];
	UINT64 timeout_tick;
	// Validate arguments
	if (name == NULL || ip == NULL)
	{
		return false;
	}

	IPToStr(name, size, ip);

	for (i = 0;i < NUM_NBT_QUERYS_SEND;i++)
	{
		tran_id[i] = Rand16();
	}

	s = NewUDP(0);
	if (s == NULL)
	{
		return false;
	}

	for (j = 0;j < NUM_NBT_QUERYS_SEND;j++)
	{
		Zero(&req, sizeof(req));
		req.TransactionId = Endian16(tran_id[j]);
		req.NumQuestions = Endian16(1);
		req.Query[0] = 0x20;
		req.Query[1] = 0x43;
		req.Query[2] = 0x4b;
		for (i = 3;i <= 32;i++)
		{
			req.Query[i] = 0x41;
		}
		req.Query[35] = 0x21;
		req.Query[37] = 0x01;

		if (SendTo(s, ip, 137, &req, sizeof(req)) == 0)
		{
			ReleaseSock(s);
			return false;
		}
	}

	timeout_tick = Tick64() + (UINT64)TIMEOUT_NETBIOS_HOSTNAME;

	while (1)
	{
		UINT ret;
		IP src_ip;
		UINT src_port;
		SOCKSET set;
		if (Tick64() >= timeout_tick)
		{
			break;
		}
		InitSockSet(&set);
		AddSockSet(&set, s);
		Select(&set, 100, NULL, NULL);

		if (flag == false)
		{
			flag = true;
		}
		else
		{
			SleepThread(10);
		}

		ret = RecvFrom(s, &src_ip, &src_port, buf, sizeof(buf));

		if (ret == SOCK_LATER)
		{
			continue;
		}
		else if (ret == 0)
		{
			break;
		}
		else
		{
			if (ret >= sizeof(NBTRESPONSE))
			{
				NBTRESPONSE *r = (NBTRESPONSE *)buf;
				bool b = false;
				UINT i;
				USHORT id = Endian16(r->TransactionId);
				for (i = 0;i < NUM_NBT_QUERYS_SEND;i++)
				{
					if (id == tran_id[i])
					{
						b = true;
						break;
					}
				}
				if (b)
				{
					if (r->Flags != 0 && r->NumQuestions == 0 && r->AnswerRRs >= 1)
					{
						if (r->Response[0] == 0x20 && r->Response[1] == 0x43 &&
							r->Response[2] == 0x4b)
						{
							if (r->Response[34] == 0x00 && r->Response[35] == 0x21 &&
								r->Response[36] == 0x00 && r->Response[37] == 0x01)
							{
								char *a = (char *)(&r->Response[45]);
								if (StrCheckLen(a, 15))
								{
									if (IsEmptyStr(a) == false)
									{
										StrCpy(name, size, a);
										Trim(name);
										ok = true;
									}
									else
									{
										ok = false;
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}

	ReleaseSock(s);
	return ok;
}