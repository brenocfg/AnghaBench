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
struct ipath_devdata {int dummy; } ;
typedef  int ipath_err_t ;

/* Variables and functions */
 int INFINIPATH_E_HARDWARE ; 
 int INFINIPATH_E_IBSTATUSCHANGED ; 
 int INFINIPATH_E_INVALIDADDR ; 
 int INFINIPATH_E_INVALIDEEPCMD ; 
 int INFINIPATH_E_PKTERRS ; 
 int INFINIPATH_E_RBADTID ; 
 int INFINIPATH_E_RBADVERSION ; 
 int INFINIPATH_E_REBP ; 
 int INFINIPATH_E_RESET ; 
 int INFINIPATH_E_RFORMATERR ; 
 int INFINIPATH_E_RHDR ; 
 int INFINIPATH_E_RHDRLEN ; 
 int INFINIPATH_E_RIBFLOW ; 
 int INFINIPATH_E_RIBLOSTLINK ; 
 int INFINIPATH_E_RICRC ; 
 int INFINIPATH_E_RLONGPKTLEN ; 
 int INFINIPATH_E_RMAXPKTLEN ; 
 int INFINIPATH_E_RMINPKTLEN ; 
 int INFINIPATH_E_RRCVEGRFULL ; 
 int INFINIPATH_E_RRCVHDRFULL ; 
 int INFINIPATH_E_RSHORTPKTLEN ; 
 int INFINIPATH_E_RUNEXPCHAR ; 
 int INFINIPATH_E_RUNSUPVL ; 
 int INFINIPATH_E_RVCRC ; 
 int INFINIPATH_E_SDMAERRS ; 
 int INFINIPATH_E_SDROPPEDDATAPKT ; 
 int INFINIPATH_E_SDROPPEDSMPPKT ; 
 int INFINIPATH_E_SENDSPECIALTRIGGER ; 
 int INFINIPATH_E_SMAXPKTLEN ; 
 int INFINIPATH_E_SMINPKTLEN ; 
 int INFINIPATH_E_SPIOARMLAUNCH ; 
 int INFINIPATH_E_SPKTLEN ; 
 int INFINIPATH_E_SUNDERRUN ; 
 int INFINIPATH_E_SUNEXPERRPKTNUM ; 
 int INFINIPATH_E_SUNSUPVL ; 
 int __IPATH_ERRPKTDBG ; 
 int /*<<< orphan*/  decode_sdma_errs (struct ipath_devdata*,int,char*,size_t) ; 
 int ipath_debug ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

int ipath_decode_err(struct ipath_devdata *dd, char *buf, size_t blen,
	ipath_err_t err)
{
	int iserr = 1;
	*buf = '\0';
	if (err & INFINIPATH_E_PKTERRS) {
		if (!(err & ~INFINIPATH_E_PKTERRS))
			iserr = 0; // if only packet errors.
		if (ipath_debug & __IPATH_ERRPKTDBG) {
			if (err & INFINIPATH_E_REBP)
				strlcat(buf, "EBP ", blen);
			if (err & INFINIPATH_E_RVCRC)
				strlcat(buf, "VCRC ", blen);
			if (err & INFINIPATH_E_RICRC) {
				strlcat(buf, "CRC ", blen);
				// clear for check below, so only once
				err &= INFINIPATH_E_RICRC;
			}
			if (err & INFINIPATH_E_RSHORTPKTLEN)
				strlcat(buf, "rshortpktlen ", blen);
			if (err & INFINIPATH_E_SDROPPEDDATAPKT)
				strlcat(buf, "sdroppeddatapkt ", blen);
			if (err & INFINIPATH_E_SPKTLEN)
				strlcat(buf, "spktlen ", blen);
		}
		if ((err & INFINIPATH_E_RICRC) &&
			!(err&(INFINIPATH_E_RVCRC|INFINIPATH_E_REBP)))
			strlcat(buf, "CRC ", blen);
		if (!iserr)
			goto done;
	}
	if (err & INFINIPATH_E_RHDRLEN)
		strlcat(buf, "rhdrlen ", blen);
	if (err & INFINIPATH_E_RBADTID)
		strlcat(buf, "rbadtid ", blen);
	if (err & INFINIPATH_E_RBADVERSION)
		strlcat(buf, "rbadversion ", blen);
	if (err & INFINIPATH_E_RHDR)
		strlcat(buf, "rhdr ", blen);
	if (err & INFINIPATH_E_SENDSPECIALTRIGGER)
		strlcat(buf, "sendspecialtrigger ", blen);
	if (err & INFINIPATH_E_RLONGPKTLEN)
		strlcat(buf, "rlongpktlen ", blen);
	if (err & INFINIPATH_E_RMAXPKTLEN)
		strlcat(buf, "rmaxpktlen ", blen);
	if (err & INFINIPATH_E_RMINPKTLEN)
		strlcat(buf, "rminpktlen ", blen);
	if (err & INFINIPATH_E_SMINPKTLEN)
		strlcat(buf, "sminpktlen ", blen);
	if (err & INFINIPATH_E_RFORMATERR)
		strlcat(buf, "rformaterr ", blen);
	if (err & INFINIPATH_E_RUNSUPVL)
		strlcat(buf, "runsupvl ", blen);
	if (err & INFINIPATH_E_RUNEXPCHAR)
		strlcat(buf, "runexpchar ", blen);
	if (err & INFINIPATH_E_RIBFLOW)
		strlcat(buf, "ribflow ", blen);
	if (err & INFINIPATH_E_SUNDERRUN)
		strlcat(buf, "sunderrun ", blen);
	if (err & INFINIPATH_E_SPIOARMLAUNCH)
		strlcat(buf, "spioarmlaunch ", blen);
	if (err & INFINIPATH_E_SUNEXPERRPKTNUM)
		strlcat(buf, "sunexperrpktnum ", blen);
	if (err & INFINIPATH_E_SDROPPEDSMPPKT)
		strlcat(buf, "sdroppedsmppkt ", blen);
	if (err & INFINIPATH_E_SMAXPKTLEN)
		strlcat(buf, "smaxpktlen ", blen);
	if (err & INFINIPATH_E_SUNSUPVL)
		strlcat(buf, "sunsupVL ", blen);
	if (err & INFINIPATH_E_INVALIDADDR)
		strlcat(buf, "invalidaddr ", blen);
	if (err & INFINIPATH_E_RRCVEGRFULL)
		strlcat(buf, "rcvegrfull ", blen);
	if (err & INFINIPATH_E_RRCVHDRFULL)
		strlcat(buf, "rcvhdrfull ", blen);
	if (err & INFINIPATH_E_IBSTATUSCHANGED)
		strlcat(buf, "ibcstatuschg ", blen);
	if (err & INFINIPATH_E_RIBLOSTLINK)
		strlcat(buf, "riblostlink ", blen);
	if (err & INFINIPATH_E_HARDWARE)
		strlcat(buf, "hardware ", blen);
	if (err & INFINIPATH_E_RESET)
		strlcat(buf, "reset ", blen);
	if (err & INFINIPATH_E_SDMAERRS)
		decode_sdma_errs(dd, err, buf, blen);
	if (err & INFINIPATH_E_INVALIDEEPCMD)
		strlcat(buf, "invalideepromcmd ", blen);
done:
	return iserr;
}