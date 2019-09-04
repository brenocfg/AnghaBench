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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */

void WriteProbe(char *filename, UINT line, char *str)
{
#ifdef	OS_WIN32
	char *s;
	char tmp[MAX_SIZE];
	char tmp2[MAX_SIZE];
	UINT64 now = 0;
	UINT64 time;

	if (IsProbeEnabled() == false)
	{
		return;
	}

	now = MsGetHiResCounter();

	Lock(probe_lock);
	{
		UINT64 diff;
		
		time = MsGetHiResTimeSpanUSec(now - probe_start);

		diff = time - probe_last;

		if (time < probe_last)
		{
			diff = 0;
		}

		probe_last = time;

		ToStr64(tmp, time);
		MakeCharArray2(tmp2, ' ', (UINT)(MIN(12, (int)12 - (int)StrLen(tmp))));
		WriteBuf(probe_buf, tmp2, StrLen(tmp2));
		WriteBuf(probe_buf, tmp, StrLen(tmp));

		s = " [+";
		WriteBuf(probe_buf, s, StrLen(s));

		ToStr64(tmp, diff);
		MakeCharArray2(tmp2, ' ', (UINT)(MIN(12, (int)12 - (int)StrLen(tmp))));
		WriteBuf(probe_buf, tmp2, StrLen(tmp2));
		WriteBuf(probe_buf, tmp, StrLen(tmp));

		s = "] - ";
		WriteBuf(probe_buf, s, StrLen(s));

		WriteBuf(probe_buf, filename, StrLen(filename));

		s = "(";
		WriteBuf(probe_buf, s, StrLen(s));

		ToStr64(tmp, (UINT64)line);
		WriteBuf(probe_buf, tmp, StrLen(tmp));

		s = "): ";
		WriteBuf(probe_buf, s, StrLen(s));

		WriteBuf(probe_buf, str, StrLen(str));

		s = "\r\n";
		WriteBuf(probe_buf, s, StrLen(s));
	}
	Unlock(probe_lock);
#endif	// OS_WIN32
}