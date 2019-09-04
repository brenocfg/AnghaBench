#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int UCHAR ;
struct TYPE_13__ {int Current; } ;
struct TYPE_12__ {int* PreMasterSecret; int* Random1; int* Random2; struct TYPE_12__* PeerInfo; struct TYPE_12__* Password; struct TYPE_12__* Username; struct TYPE_12__* OptionString; } ;
typedef  TYPE_1__ OPENVPN_KEY_METHOD_2 ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_2__* NewBuf () ; 
 scalar_t__ OvsReadStringFromBuf (TYPE_2__*,TYPE_1__*,int) ; 
 int ReadBuf (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT OvsParseKeyMethod2(OPENVPN_KEY_METHOD_2 *ret, UCHAR *data, UINT size, bool client_mode)
{
	BUF *b;
	UINT read_size = 0;
	UINT ui;
	UCHAR uc;
	// Validate arguments
	Zero(ret, sizeof(OPENVPN_KEY_METHOD_2));
	if (ret == NULL || data == NULL || size == 0)
	{
		return 0;
	}

	b = NewBuf();
	WriteBuf(b, data, size);
	SeekBuf(b, 0, 0);

	// Reserved
	if (ReadBuf(b, &ui, sizeof(UINT)) == sizeof(UINT))
	{
		// Method
		if (ReadBuf(b, &uc, sizeof(UCHAR)) == sizeof(UCHAR) && uc == 2)
		{
			// Pre Master Secret
			if (client_mode == false || ReadBuf(b, ret->PreMasterSecret, sizeof(ret->PreMasterSecret)) == sizeof(ret->PreMasterSecret))
			{
				// Random1
				if (ReadBuf(b, ret->Random1, sizeof(ret->Random1)) == sizeof(ret->Random1))
				{
					// Random2
					if (ReadBuf(b, ret->Random2, sizeof(ret->Random2)) == sizeof(ret->Random2))
					{
						// String
						if (OvsReadStringFromBuf(b, ret->OptionString, sizeof(ret->OptionString)) &&
							OvsReadStringFromBuf(b, ret->Username, sizeof(ret->Username)) &&
							OvsReadStringFromBuf(b, ret->Password, sizeof(ret->Password)))
							{
								if (!OvsReadStringFromBuf(b, ret->PeerInfo, sizeof(ret->PeerInfo)))
								{
									Zero(ret->PeerInfo, sizeof(ret->PeerInfo));
								}
							read_size = b->Current;
						}
					}
				}
			}
		}
	}

	FreeBuf(b);

	return read_size;
}