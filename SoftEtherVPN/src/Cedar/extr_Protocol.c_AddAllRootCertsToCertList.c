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
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AddXToCertList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PackGetBufEx (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ROOT_CERTS_FILENAME ; 
 int /*<<< orphan*/ * ReadDump (int /*<<< orphan*/ ) ; 

void AddAllRootCertsToCertList(LIST *o)
{
	BUF *buf;
	PACK *p;
	UINT num_ok = 0, num_error = 0;
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	buf = ReadDump(ROOT_CERTS_FILENAME);
	if (buf == NULL)
	{
		return;
	}

	p = BufToPack(buf);

	if (p != NULL)
	{
		UINT num = PackGetIndexCount(p, "cert");
		UINT i;

		for (i = 0;i < num;i++)
		{
			bool ok = false;
			BUF *b = PackGetBufEx(p, "cert", i);

			if (b != NULL)
			{
				X *x = BufToX(b, false);

				if (x != NULL)
				{
					AddXToCertList(o, x);

					ok = true;

					FreeX(x);
				}

				FreeBuf(b);
			}

			if (ok)
			{
				num_ok++;
			}
			else
			{
				num_error++;
			}
		}

		FreePack(p);
	}

	FreeBuf(buf);

	Debug("AddAllRootCertsToCertList: ok=%u error=%u total_list_len=%u\n", num_ok, num_error, LIST_NUM(o));
}