#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct xdrbuf {int /*<<< orphan*/  xb_flags; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct TYPE_22__ {scalar_t__ nli_flags; scalar_t__ nli_loc; scalar_t__ nli_serv; scalar_t__ nli_addr; } ;
struct TYPE_12__ {scalar_t__ nl_numlocs; TYPE_9__ nl_current; TYPE_8__** nl_locations; } ;
struct TYPE_17__ {scalar_t__ selected; scalar_t__ count; scalar_t__* etypes; } ;
struct TYPE_16__ {int count; scalar_t__* flavors; } ;
struct TYPE_15__ {int count; scalar_t__* flavors; } ;
struct TYPE_14__ {scalar_t__* nfsa_supp_attr; } ;
struct nfsmount {int nm_state; scalar_t__ nm_lockmode; scalar_t__ nm_vers; scalar_t__ nm_mountport; int nm_deadtimeout; char* nm_realm; char* nm_principal; char* nm_sprinc; scalar_t__ nm_sotype; scalar_t__ nm_minor_vers; scalar_t__ nm_rsize; scalar_t__ nm_wsize; scalar_t__ nm_readdirsize; scalar_t__ nm_readahead; scalar_t__ nm_acregmin; scalar_t__ nm_acregmax; scalar_t__ nm_acdirmin; scalar_t__ nm_acdirmax; scalar_t__ nm_auth; scalar_t__ nm_numgrps; scalar_t__ nm_sofamily; int nm_timeo; scalar_t__ nm_retry; TYPE_10__ nm_locations; int /*<<< orphan*/  nm_mountp; TYPE_5__* nm_fh; scalar_t__ nm_saddr; TYPE_4__ nm_etype; TYPE_3__ nm_servsec; TYPE_2__ nm_sec; int /*<<< orphan*/ * nm_args; TYPE_1__ nm_fsattr; } ;
typedef  int /*<<< orphan*/  sotype ;
struct TYPE_20__ {scalar_t__ np_compcount; char** np_components; } ;
struct TYPE_21__ {scalar_t__ nl_servcount; TYPE_7__ nl_path; TYPE_6__** nl_servers; } ;
struct TYPE_19__ {char* ns_name; scalar_t__ ns_addrcount; char** ns_addresses; } ;
struct TYPE_18__ {int /*<<< orphan*/  fh_len; int /*<<< orphan*/ * fh_data; } ;
struct TYPE_13__ {char* f_mntfromname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACLONLY ; 
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  CALLUMNT ; 
 int /*<<< orphan*/  DUMBTIMER ; 
 int /*<<< orphan*/  EPHEMERAL ; 
 int /*<<< orphan*/  INTR ; 
 int /*<<< orphan*/  MNTQUICK ; 
 int /*<<< orphan*/  MNTUDP ; 
 int /*<<< orphan*/  MUTEJUKEBOX ; 
 int /*<<< orphan*/  NAMEDATTR ; 
 int /*<<< orphan*/  NFC ; 
 int NFSSTA_DEAD ; 
 int NFSSTA_JUKEBOXTIMEO ; 
 int NFSSTA_LOCKTIMEO ; 
 int NFSSTA_RECOVER ; 
 int NFSSTA_TIMEO ; 
 scalar_t__ NFS_ARGSVERSION_XDR ; 
 scalar_t__ NFS_BITMAP_ISSET (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_BITMAP_SET (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_BITMAP_ZERO (scalar_t__*,int) ; 
 int /*<<< orphan*/  NFS_FATTR_QUOTA_AVAIL_HARD ; 
 int /*<<< orphan*/  NFS_FATTR_QUOTA_AVAIL_SOFT ; 
 int /*<<< orphan*/  NFS_FATTR_QUOTA_USED ; 
 int NFS_HZ ; 
 scalar_t__ NFS_LOCK_MODE_ENABLED ; 
 int /*<<< orphan*/  NFS_MATTR_ATTRCACHE_DIR_MAX ; 
 int /*<<< orphan*/  NFS_MATTR_ATTRCACHE_DIR_MIN ; 
 int /*<<< orphan*/  NFS_MATTR_ATTRCACHE_REG_MAX ; 
 int /*<<< orphan*/  NFS_MATTR_ATTRCACHE_REG_MIN ; 
 int NFS_MATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MATTR_DEAD_TIMEOUT ; 
 int /*<<< orphan*/  NFS_MATTR_FH ; 
 int /*<<< orphan*/  NFS_MATTR_FLAGS ; 
 int /*<<< orphan*/  NFS_MATTR_FS_LOCATIONS ; 
 int /*<<< orphan*/  NFS_MATTR_KERB_ETYPE ; 
 int /*<<< orphan*/  NFS_MATTR_LOCK_MODE ; 
 int /*<<< orphan*/  NFS_MATTR_MAX_GROUP_LIST ; 
 int /*<<< orphan*/  NFS_MATTR_MNTFLAGS ; 
 int /*<<< orphan*/  NFS_MATTR_MNTFROM ; 
 int /*<<< orphan*/  NFS_MATTR_MOUNT_PORT ; 
 int /*<<< orphan*/  NFS_MATTR_NFS_MINOR_VERSION ; 
 int /*<<< orphan*/  NFS_MATTR_NFS_PORT ; 
 int /*<<< orphan*/  NFS_MATTR_NFS_VERSION ; 
 int /*<<< orphan*/  NFS_MATTR_PRINCIPAL ; 
 int /*<<< orphan*/  NFS_MATTR_READAHEAD ; 
 int /*<<< orphan*/  NFS_MATTR_READDIR_SIZE ; 
 int /*<<< orphan*/  NFS_MATTR_READ_SIZE ; 
 int /*<<< orphan*/  NFS_MATTR_REALM ; 
 int /*<<< orphan*/  NFS_MATTR_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  NFS_MATTR_SECURITY ; 
 int /*<<< orphan*/  NFS_MATTR_SOCKET_TYPE ; 
 int /*<<< orphan*/  NFS_MATTR_SOFT_RETRY_COUNT ; 
 int /*<<< orphan*/  NFS_MATTR_SVCPRINCIPAL ; 
 int /*<<< orphan*/  NFS_MATTR_WRITE_SIZE ; 
 int /*<<< orphan*/  NFS_MFLAG_ACLONLY ; 
 int NFS_MFLAG_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MFLAG_CALLUMNT ; 
 int /*<<< orphan*/  NFS_MFLAG_DUMBTIMER ; 
 int /*<<< orphan*/  NFS_MFLAG_EPHEMERAL ; 
 int /*<<< orphan*/  NFS_MFLAG_INTR ; 
 int /*<<< orphan*/  NFS_MFLAG_MNTQUICK ; 
 int /*<<< orphan*/  NFS_MFLAG_MNTUDP ; 
 int /*<<< orphan*/  NFS_MFLAG_MUTEJUKEBOX ; 
 int /*<<< orphan*/  NFS_MFLAG_NAMEDATTR ; 
 int /*<<< orphan*/  NFS_MFLAG_NFC ; 
 int /*<<< orphan*/  NFS_MFLAG_NOACL ; 
 int /*<<< orphan*/  NFS_MFLAG_NOCALLBACK ; 
 int /*<<< orphan*/  NFS_MFLAG_NOCONNECT ; 
 int /*<<< orphan*/  NFS_MFLAG_NONEGNAMECACHE ; 
 int /*<<< orphan*/  NFS_MFLAG_NOQUOTA ; 
 int /*<<< orphan*/  NFS_MFLAG_RDIRPLUS ; 
 int /*<<< orphan*/  NFS_MFLAG_RESVPORT ; 
 int /*<<< orphan*/  NFS_MFLAG_SOFT ; 
 int NFS_MIATTR_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MIATTR_CUR_ARGS ; 
 int /*<<< orphan*/  NFS_MIATTR_CUR_LOC_INDEX ; 
 int /*<<< orphan*/  NFS_MIATTR_FLAGS ; 
 int /*<<< orphan*/  NFS_MIATTR_ORIG_ARGS ; 
 int NFS_MIFLAG_BITMAP_LEN ; 
 int /*<<< orphan*/  NFS_MIFLAG_DEAD ; 
 int /*<<< orphan*/  NFS_MIFLAG_NOTRESP ; 
 int /*<<< orphan*/  NFS_MIFLAG_RECOVERY ; 
 scalar_t__ NFS_MOUNT_INFO_VERSION ; 
 scalar_t__ NFS_VER3 ; 
 scalar_t__ NFS_VER4 ; 
 scalar_t__ NFS_XDRARGS_VERSION_0 ; 
 scalar_t__ NMFLAG (struct nfsmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOACL ; 
 int /*<<< orphan*/  NOCALLBACK ; 
 int /*<<< orphan*/  NOCONNECT ; 
 int /*<<< orphan*/  NONEGNAMECACHE ; 
 int /*<<< orphan*/  NOQUOTA ; 
 int /*<<< orphan*/  RDIRPLUS ; 
 int /*<<< orphan*/  RESVPORT ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  SOFT ; 
 int /*<<< orphan*/  XB_CLEANUP ; 
 int XDRWORD ; 
 int /*<<< orphan*/  nfsmerr_if (int) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ vfs_flags (int /*<<< orphan*/ ) ; 
 TYPE_11__* vfs_statfs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_add_32 (int,struct xdrbuf*,scalar_t__) ; 
 int /*<<< orphan*/  xb_add_bitmap (int,struct xdrbuf*,scalar_t__*,int) ; 
 int xb_add_bytes (struct xdrbuf*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_add_fh (int,struct xdrbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_add_string (int,struct xdrbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xb_build_done (int,struct xdrbuf*) ; 
 int /*<<< orphan*/  xb_cleanup (struct xdrbuf*) ; 
 int /*<<< orphan*/  xb_get_32 (int,struct xdrbuf*,scalar_t__) ; 
 int /*<<< orphan*/  xb_init_buffer (struct xdrbuf*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ xb_offset (struct xdrbuf*) ; 
 int xb_seek (struct xdrbuf*,scalar_t__) ; 

int
nfs_mountinfo_assemble(struct nfsmount *nmp, struct xdrbuf *xb)
{
	struct xdrbuf xbinfo, xborig;
	char sotype[6];
	uint32_t origargsvers, origargslength;
	uint32_t infolength_offset, curargsopaquelength_offset, curargslength_offset, attrslength_offset, curargs_end_offset, end_offset;
	uint32_t miattrs[NFS_MIATTR_BITMAP_LEN];
	uint32_t miflags_mask[NFS_MIFLAG_BITMAP_LEN];
	uint32_t miflags[NFS_MIFLAG_BITMAP_LEN];
	uint32_t mattrs[NFS_MATTR_BITMAP_LEN];
	uint32_t mflags_mask[NFS_MFLAG_BITMAP_LEN];
	uint32_t mflags[NFS_MFLAG_BITMAP_LEN];
	uint32_t loc, serv, addr, comp;
	int i, timeo, error = 0;

	/* set up mount info attr and flag bitmaps */
	NFS_BITMAP_ZERO(miattrs, NFS_MIATTR_BITMAP_LEN);
	NFS_BITMAP_SET(miattrs, NFS_MIATTR_FLAGS);
	NFS_BITMAP_SET(miattrs, NFS_MIATTR_ORIG_ARGS);
	NFS_BITMAP_SET(miattrs, NFS_MIATTR_CUR_ARGS);
	NFS_BITMAP_SET(miattrs, NFS_MIATTR_CUR_LOC_INDEX);
	NFS_BITMAP_ZERO(miflags_mask, NFS_MIFLAG_BITMAP_LEN);
	NFS_BITMAP_ZERO(miflags, NFS_MIFLAG_BITMAP_LEN);
	NFS_BITMAP_SET(miflags_mask, NFS_MIFLAG_DEAD);
	NFS_BITMAP_SET(miflags_mask, NFS_MIFLAG_NOTRESP);
	NFS_BITMAP_SET(miflags_mask, NFS_MIFLAG_RECOVERY);
	if (nmp->nm_state & NFSSTA_DEAD)
		NFS_BITMAP_SET(miflags, NFS_MIFLAG_DEAD);
	if ((nmp->nm_state & (NFSSTA_TIMEO|NFSSTA_JUKEBOXTIMEO)) ||
	    ((nmp->nm_state & NFSSTA_LOCKTIMEO) && (nmp->nm_lockmode == NFS_LOCK_MODE_ENABLED)))
		NFS_BITMAP_SET(miflags, NFS_MIFLAG_NOTRESP);
	if (nmp->nm_state & NFSSTA_RECOVER)
		NFS_BITMAP_SET(miflags, NFS_MIFLAG_RECOVERY);

	/* get original mount args length */
	xb_init_buffer(&xborig, nmp->nm_args, 2*XDRWORD);
	xb_get_32(error, &xborig, origargsvers); /* version */
	xb_get_32(error, &xborig, origargslength); /* args length */
	nfsmerr_if(error);

	/* set up current mount attributes bitmap */
	NFS_BITMAP_ZERO(mattrs, NFS_MATTR_BITMAP_LEN);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_FLAGS);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_NFS_VERSION);
	if (nmp->nm_vers >= NFS_VER4)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_NFS_MINOR_VERSION);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_READ_SIZE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_WRITE_SIZE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_READDIR_SIZE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_READAHEAD);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_ATTRCACHE_REG_MIN);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_ATTRCACHE_REG_MAX);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_ATTRCACHE_DIR_MIN);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_ATTRCACHE_DIR_MAX);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_LOCK_MODE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_SECURITY);
	if (nmp->nm_etype.selected < nmp->nm_etype.count)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_KERB_ETYPE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_MAX_GROUP_LIST);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_SOCKET_TYPE);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_NFS_PORT);
	if ((nmp->nm_vers < NFS_VER4) && nmp->nm_mountport)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_MOUNT_PORT);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_REQUEST_TIMEOUT);
	if (NMFLAG(nmp, SOFT))
		NFS_BITMAP_SET(mattrs, NFS_MATTR_SOFT_RETRY_COUNT);
	if (nmp->nm_deadtimeout)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_DEAD_TIMEOUT);
	if (nmp->nm_fh)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_FH);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_FS_LOCATIONS);
	NFS_BITMAP_SET(mattrs, NFS_MATTR_MNTFLAGS);
	if (origargsvers < NFS_ARGSVERSION_XDR)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_MNTFROM);
	if (nmp->nm_realm)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_REALM);
	if (nmp->nm_principal)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_PRINCIPAL);
	if (nmp->nm_sprinc)
		NFS_BITMAP_SET(mattrs, NFS_MATTR_SVCPRINCIPAL);
	
	/* set up current mount flags bitmap */
	/* first set the flags that we will be setting - either on OR off */
	NFS_BITMAP_ZERO(mflags_mask, NFS_MFLAG_BITMAP_LEN);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_SOFT);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_INTR);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_RESVPORT);
	if (nmp->nm_sotype == SOCK_DGRAM)
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NOCONNECT);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_DUMBTIMER);
	if (nmp->nm_vers < NFS_VER4)
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_CALLUMNT);
	if (nmp->nm_vers >= NFS_VER3)
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_RDIRPLUS);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NONEGNAMECACHE);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_MUTEJUKEBOX);
	if (nmp->nm_vers >= NFS_VER4) {
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_EPHEMERAL);
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NOCALLBACK);
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NAMEDATTR);
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NOACL);
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_ACLONLY);
	}
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NFC);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_NOQUOTA);
	if (nmp->nm_vers < NFS_VER4)
		NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_MNTUDP);
	NFS_BITMAP_SET(mflags_mask, NFS_MFLAG_MNTQUICK);
	/* now set the flags that should be set */
	NFS_BITMAP_ZERO(mflags, NFS_MFLAG_BITMAP_LEN);
	if (NMFLAG(nmp, SOFT))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_SOFT);
	if (NMFLAG(nmp, INTR))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_INTR);
	if (NMFLAG(nmp, RESVPORT))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_RESVPORT);
	if ((nmp->nm_sotype == SOCK_DGRAM) && NMFLAG(nmp, NOCONNECT))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_NOCONNECT);
	if (NMFLAG(nmp, DUMBTIMER))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_DUMBTIMER);
	if ((nmp->nm_vers < NFS_VER4) && NMFLAG(nmp, CALLUMNT))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_CALLUMNT);
	if ((nmp->nm_vers >= NFS_VER3) && NMFLAG(nmp, RDIRPLUS))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_RDIRPLUS);
	if (NMFLAG(nmp, NONEGNAMECACHE))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_NONEGNAMECACHE);
	if (NMFLAG(nmp, MUTEJUKEBOX))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_MUTEJUKEBOX);
	if (nmp->nm_vers >= NFS_VER4) {
		if (NMFLAG(nmp, EPHEMERAL))
			NFS_BITMAP_SET(mflags, NFS_MFLAG_EPHEMERAL);
		if (NMFLAG(nmp, NOCALLBACK))
			NFS_BITMAP_SET(mflags, NFS_MFLAG_NOCALLBACK);
		if (NMFLAG(nmp, NAMEDATTR))
			NFS_BITMAP_SET(mflags, NFS_MFLAG_NAMEDATTR);
		if (NMFLAG(nmp, NOACL))
			NFS_BITMAP_SET(mflags, NFS_MFLAG_NOACL);
		if (NMFLAG(nmp, ACLONLY))
			NFS_BITMAP_SET(mflags, NFS_MFLAG_ACLONLY);
	}
	if (NMFLAG(nmp, NFC))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_NFC);
	if (NMFLAG(nmp, NOQUOTA) || ((nmp->nm_vers >= NFS_VER4) &&
	    !NFS_BITMAP_ISSET(nmp->nm_fsattr.nfsa_supp_attr, NFS_FATTR_QUOTA_AVAIL_HARD) &&
	    !NFS_BITMAP_ISSET(nmp->nm_fsattr.nfsa_supp_attr, NFS_FATTR_QUOTA_AVAIL_SOFT) &&
	    !NFS_BITMAP_ISSET(nmp->nm_fsattr.nfsa_supp_attr, NFS_FATTR_QUOTA_USED)))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_NOQUOTA);
	if ((nmp->nm_vers < NFS_VER4) && NMFLAG(nmp, MNTUDP))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_MNTUDP);
	if (NMFLAG(nmp, MNTQUICK))
		NFS_BITMAP_SET(mflags, NFS_MFLAG_MNTQUICK);

	/* assemble info buffer: */
	xb_init_buffer(&xbinfo, NULL, 0);
	xb_add_32(error, &xbinfo, NFS_MOUNT_INFO_VERSION);
	infolength_offset = xb_offset(&xbinfo);
	xb_add_32(error, &xbinfo, 0);
	xb_add_bitmap(error, &xbinfo, miattrs, NFS_MIATTR_BITMAP_LEN);
	xb_add_bitmap(error, &xbinfo, miflags, NFS_MIFLAG_BITMAP_LEN);
	xb_add_32(error, &xbinfo, origargslength);
	if (!error)
		error = xb_add_bytes(&xbinfo, nmp->nm_args, origargslength, 0);

	/* the opaque byte count for the current mount args values: */
	curargsopaquelength_offset = xb_offset(&xbinfo);
	xb_add_32(error, &xbinfo, 0);

	/* Encode current mount args values */
	xb_add_32(error, &xbinfo, NFS_ARGSVERSION_XDR);
	curargslength_offset = xb_offset(&xbinfo);
	xb_add_32(error, &xbinfo, 0);
	xb_add_32(error, &xbinfo, NFS_XDRARGS_VERSION_0);
	xb_add_bitmap(error, &xbinfo, mattrs, NFS_MATTR_BITMAP_LEN);
	attrslength_offset = xb_offset(&xbinfo);
	xb_add_32(error, &xbinfo, 0);
	xb_add_bitmap(error, &xbinfo, mflags_mask, NFS_MFLAG_BITMAP_LEN);
	xb_add_bitmap(error, &xbinfo, mflags, NFS_MFLAG_BITMAP_LEN);
	xb_add_32(error, &xbinfo, nmp->nm_vers);		/* NFS_VERSION */
	if (nmp->nm_vers >= NFS_VER4)
		xb_add_32(error, &xbinfo, nmp->nm_minor_vers);	/* NFS_MINOR_VERSION */
	xb_add_32(error, &xbinfo, nmp->nm_rsize);		/* READ_SIZE */
	xb_add_32(error, &xbinfo, nmp->nm_wsize);		/* WRITE_SIZE */
	xb_add_32(error, &xbinfo, nmp->nm_readdirsize);		/* READDIR_SIZE */
	xb_add_32(error, &xbinfo, nmp->nm_readahead);		/* READAHEAD */
	xb_add_32(error, &xbinfo, nmp->nm_acregmin);		/* ATTRCACHE_REG_MIN */
	xb_add_32(error, &xbinfo, 0);				/* ATTRCACHE_REG_MIN */
	xb_add_32(error, &xbinfo, nmp->nm_acregmax);		/* ATTRCACHE_REG_MAX */
	xb_add_32(error, &xbinfo, 0);				/* ATTRCACHE_REG_MAX */
	xb_add_32(error, &xbinfo, nmp->nm_acdirmin);		/* ATTRCACHE_DIR_MIN */
	xb_add_32(error, &xbinfo, 0);				/* ATTRCACHE_DIR_MIN */
	xb_add_32(error, &xbinfo, nmp->nm_acdirmax);		/* ATTRCACHE_DIR_MAX */
	xb_add_32(error, &xbinfo, 0);				/* ATTRCACHE_DIR_MAX */
	xb_add_32(error, &xbinfo, nmp->nm_lockmode);		/* LOCK_MODE */
	if (nmp->nm_sec.count) {
		xb_add_32(error, &xbinfo, nmp->nm_sec.count);		/* SECURITY */
		nfsmerr_if(error);
		for (i=0; i < nmp->nm_sec.count; i++)
			xb_add_32(error, &xbinfo, nmp->nm_sec.flavors[i]);
	} else if (nmp->nm_servsec.count) {
		xb_add_32(error, &xbinfo, nmp->nm_servsec.count);	/* SECURITY */
		nfsmerr_if(error);
		for (i=0; i < nmp->nm_servsec.count; i++)
			xb_add_32(error, &xbinfo, nmp->nm_servsec.flavors[i]);
	} else {
		xb_add_32(error, &xbinfo, 1);				/* SECURITY */
		xb_add_32(error, &xbinfo, nmp->nm_auth);
	}
	if (nmp->nm_etype.selected < nmp->nm_etype.count) {
		xb_add_32(error, &xbinfo, nmp->nm_etype.count);
		xb_add_32(error, &xbinfo, nmp->nm_etype.selected);
		for (uint32_t j=0; j < nmp->nm_etype.count; j++)
			xb_add_32(error, &xbinfo, nmp->nm_etype.etypes[j]);
		nfsmerr_if(error);
	}
	xb_add_32(error, &xbinfo, nmp->nm_numgrps);		/* MAX_GROUP_LIST */
	nfsmerr_if(error);
	snprintf(sotype, sizeof(sotype), "%s%s", (nmp->nm_sotype == SOCK_DGRAM) ? "udp" : "tcp",
		nmp->nm_sofamily ? (nmp->nm_sofamily == AF_INET) ? "4" : "6" : "");
	xb_add_string(error, &xbinfo, sotype, strlen(sotype));	/* SOCKET_TYPE */
	xb_add_32(error, &xbinfo, ntohs(((struct sockaddr_in*)nmp->nm_saddr)->sin_port)); /* NFS_PORT */
	if ((nmp->nm_vers < NFS_VER4) && nmp->nm_mountport)
		xb_add_32(error, &xbinfo, nmp->nm_mountport);	/* MOUNT_PORT */
	timeo = (nmp->nm_timeo * 10) / NFS_HZ;
	xb_add_32(error, &xbinfo, timeo/10);			/* REQUEST_TIMEOUT */
	xb_add_32(error, &xbinfo, (timeo%10)*100000000);	/* REQUEST_TIMEOUT */
	if (NMFLAG(nmp, SOFT))
		xb_add_32(error, &xbinfo, nmp->nm_retry);	/* SOFT_RETRY_COUNT */
	if (nmp->nm_deadtimeout) {
		xb_add_32(error, &xbinfo, nmp->nm_deadtimeout);	/* DEAD_TIMEOUT */
		xb_add_32(error, &xbinfo, 0);			/* DEAD_TIMEOUT */
	}
	if (nmp->nm_fh)
		xb_add_fh(error, &xbinfo, &nmp->nm_fh->fh_data[0], nmp->nm_fh->fh_len); /* FH */
	xb_add_32(error, &xbinfo, nmp->nm_locations.nl_numlocs);			/* FS_LOCATIONS */
	for (loc = 0; !error && (loc < nmp->nm_locations.nl_numlocs); loc++) {
		xb_add_32(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_servcount);
		for (serv = 0; !error && (serv < nmp->nm_locations.nl_locations[loc]->nl_servcount); serv++) {
			xb_add_string(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_name,
				strlen(nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_name));
			xb_add_32(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_addrcount);
			for (addr = 0; !error && (addr < nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_addrcount); addr++)
				xb_add_string(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_addresses[addr],
					strlen(nmp->nm_locations.nl_locations[loc]->nl_servers[serv]->ns_addresses[addr]));
			xb_add_32(error, &xbinfo, 0); /* empty server info */
		}
		xb_add_32(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_path.np_compcount);
		for (comp = 0; !error && (comp < nmp->nm_locations.nl_locations[loc]->nl_path.np_compcount); comp++)
			xb_add_string(error, &xbinfo, nmp->nm_locations.nl_locations[loc]->nl_path.np_components[comp],
				strlen(nmp->nm_locations.nl_locations[loc]->nl_path.np_components[comp]));
		xb_add_32(error, &xbinfo, 0); /* empty fs location info */
	}
	xb_add_32(error, &xbinfo, vfs_flags(nmp->nm_mountp));		/* MNTFLAGS */
	if (origargsvers < NFS_ARGSVERSION_XDR)
		xb_add_string(error, &xbinfo, vfs_statfs(nmp->nm_mountp)->f_mntfromname,
			strlen(vfs_statfs(nmp->nm_mountp)->f_mntfromname));	/* MNTFROM */
	if (NFS_BITMAP_ISSET(mattrs, NFS_MATTR_REALM))
		xb_add_string(error, &xbinfo, nmp->nm_realm, strlen(nmp->nm_realm));
	if (NFS_BITMAP_ISSET(mattrs, NFS_MATTR_PRINCIPAL))
		xb_add_string(error, &xbinfo, nmp->nm_principal, strlen(nmp->nm_principal));
	if (NFS_BITMAP_ISSET(mattrs, NFS_MATTR_SVCPRINCIPAL))
		xb_add_string(error, &xbinfo, nmp->nm_sprinc, strlen(nmp->nm_sprinc));

	curargs_end_offset = xb_offset(&xbinfo);

	/* NFS_MIATTR_CUR_LOC_INDEX */
	xb_add_32(error, &xbinfo, nmp->nm_locations.nl_current.nli_flags);
	xb_add_32(error, &xbinfo, nmp->nm_locations.nl_current.nli_loc);
	xb_add_32(error, &xbinfo, nmp->nm_locations.nl_current.nli_serv);
	xb_add_32(error, &xbinfo, nmp->nm_locations.nl_current.nli_addr);

	xb_build_done(error, &xbinfo);

	/* update opaque counts */
	end_offset = xb_offset(&xbinfo);
	if (!error) {
		error = xb_seek(&xbinfo, attrslength_offset);
		xb_add_32(error, &xbinfo, curargs_end_offset - attrslength_offset - XDRWORD/*don't include length field*/);
	}
	if (!error) {
		error = xb_seek(&xbinfo, curargslength_offset);
		xb_add_32(error, &xbinfo, curargs_end_offset - curargslength_offset + XDRWORD/*version*/);
	}
	if (!error) {
		error = xb_seek(&xbinfo, curargsopaquelength_offset);
		xb_add_32(error, &xbinfo, curargs_end_offset - curargslength_offset + XDRWORD/*version*/);
	}
	if (!error) {
		error = xb_seek(&xbinfo, infolength_offset);
		xb_add_32(error, &xbinfo, end_offset - infolength_offset + XDRWORD/*version*/);
	}
	nfsmerr_if(error);

	/* copy result xdrbuf to caller */
	*xb = xbinfo;

	/* and mark the local copy as not needing cleanup */
	xbinfo.xb_flags &= ~XB_CLEANUP;
nfsmerr:
	xb_cleanup(&xbinfo);
	return (error);
}