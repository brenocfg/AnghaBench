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
typedef  int u_char ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int DecodeASyncParams (int,int*) ; 
 int DecodeSyncParams (int,int) ; 
 int* findie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char
DecodeSI2(struct sk_buff *skb)
{
	u_char *p;		//, *pend=skb->data + skb->len;

	if ((p = findie(skb->data, skb->len, 0x7c, 0))) {
		switch (p[4] & 0x0f) {
			case 0x01:
				if (p[1] == 0x04)	// sync. Bitratenadaption

					return DecodeSyncParams(160, p[5]);	// V.110/X.30

				else if (p[1] == 0x06)	// async. Bitratenadaption

					return DecodeASyncParams(192, p);	// V.110/X.30

				break;
			case 0x08:	// if (p[5] == 0x02) // sync. Bitratenadaption
				if (p[1] > 3) 
					return DecodeSyncParams(176, p[5]);	// V.120
				break;
		}
	}
	return 0;
}