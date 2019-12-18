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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  dhcpol_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int DHCP_LEN_OFFSET ; 
 int DHCP_OPTION_OFFSET ; 
 int DHCP_TAG_OFFSET ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dhcpol_add (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  dhcpol_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dhcpol_init (int /*<<< orphan*/ *) ; 
#define  dhcptag_end_e 129 
#define  dhcptag_pad_e 128 
 int /*<<< orphan*/  dprintf (char*) ; 

boolean_t
dhcpol_parse_buffer(dhcpol_t * list, const void * buffer, int length)
{
    int			len;
    const uint8_t *	scan;
    uint8_t		tag;

    dhcpol_init(list);

    len = length;
    tag = dhcptag_pad_e;
    for (scan = (const uint8_t *)buffer;
	 tag != dhcptag_end_e && len > DHCP_TAG_OFFSET; ) {

	tag = scan[DHCP_TAG_OFFSET];

	switch (tag) {
	  case dhcptag_end_e:
	      /* remember that it was terminated */
	      dhcpol_add(list, scan);
	      scan++;
	      len--;
	      break;
	  case dhcptag_pad_e: /* ignore pad */
	      scan++;
	      len--;
	      break;
	  default:
	      if (len > DHCP_LEN_OFFSET) {
		  uint8_t	option_len;

		  option_len = scan[DHCP_LEN_OFFSET];
		  dhcpol_add(list, scan);
		  len -= (option_len + DHCP_OPTION_OFFSET);
		  scan += (option_len + DHCP_OPTION_OFFSET);
	      }
	      else {
		  len = -1;
	      }
	      break;
	}
    }
    if (len < 0) {
	/* ran off the end */
	dprintf(("dhcp_options: parse failed near tag %d\n", tag));
	dhcpol_free(list);
	return (FALSE);
    }
    return (TRUE);
}