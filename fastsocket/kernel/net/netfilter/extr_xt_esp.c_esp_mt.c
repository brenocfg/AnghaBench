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
struct xt_match_param {scalar_t__ fragoff; int* hotdrop; int /*<<< orphan*/  thoff; struct xt_esp* matchinfo; } ;
struct xt_esp {int invflags; int /*<<< orphan*/ * spis; } ;
struct sk_buff {int dummy; } ;
struct ip_esp_hdr {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  _esp ;

/* Variables and functions */
 int XT_ESP_INV_SPI ; 
 int /*<<< orphan*/  duprintf (char*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct ip_esp_hdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct ip_esp_hdr*) ; 
 int spi_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool esp_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct ip_esp_hdr *eh;
	struct ip_esp_hdr _esp;
	const struct xt_esp *espinfo = par->matchinfo;

	/* Must not be a fragment. */
	if (par->fragoff != 0)
		return false;

	eh = skb_header_pointer(skb, par->thoff, sizeof(_esp), &_esp);
	if (eh == NULL) {
		/* We've been asked to examine this packet, and we
		 * can't.  Hence, no choice but to drop.
		 */
		duprintf("Dropping evil ESP tinygram.\n");
		*par->hotdrop = true;
		return false;
	}

	return spi_match(espinfo->spis[0], espinfo->spis[1], ntohl(eh->spi),
			 !!(espinfo->invflags & XT_ESP_INV_SPI));
}