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

/* Variables and functions */
#define  UPNPCOMMAND_INVALID_ARGS 133 
#define  UPNPCOMMAND_INVALID_RESPONSE 132 
#define  UPNPCOMMAND_SUCCESS 131 
#define  UPNPCOMMAND_UNKNOWN_ERROR 130 
#define  UPNPDISCOVER_MEMORY_ERROR 129 
#define  UPNPDISCOVER_SOCKET_ERROR 128 

const char * strupnperror(int err)
{
	const char * s = NULL;
	switch(err) {
	case UPNPCOMMAND_SUCCESS:
		s = "Success";
		break;
	case UPNPCOMMAND_UNKNOWN_ERROR:
		s = "Miniupnpc Unknown Error";
		break;
	case UPNPCOMMAND_INVALID_ARGS:
		s = "Miniupnpc Invalid Arguments";
		break;
	case UPNPCOMMAND_INVALID_RESPONSE:
		s = "Miniupnpc Invalid response";
		break;
	case UPNPDISCOVER_SOCKET_ERROR:
		s = "Miniupnpc Socket error";
		break;
	case UPNPDISCOVER_MEMORY_ERROR:
		s = "Miniupnpc Memory allocation error";
		break;
	case 401:
		s = "Invalid Action";
		break;
	case 402:
		s = "Invalid Args";
		break;
	case 501:
		s = "Action Failed";
		break;
	case 606:
		s = "Action not authorized";
		break;
	case 701:
		s = "PinholeSpaceExhausted";
		break;
	case 702:
		s = "FirewallDisabled";
		break;
	case 703:
		s = "InboundPinholeNotAllowed";
		break;
	case 704:
		s = "NoSuchEntry";
		break;
	case 705:
		s = "ProtocolNotSupported";
		break;
	case 706:
		s = "InternalPortWildcardingNotAllowed";
		break;
	case 707:
		s = "ProtocolWildcardingNotAllowed";
		break;
	case 708:
		s = "WildcardNotPermittedInSrcIP";
		break;
	case 709:
		s = "NoPacketSent";
		break;
	case 713:
		s = "SpecifiedArrayIndexInvalid";
		break;
	case 714:
		s = "NoSuchEntryInArray";
		break;
	case 715:
		s = "WildCardNotPermittedInSrcIP";
		break;
	case 716:
		s = "WildCardNotPermittedInExtPort";
		break;
	case 718:
		s = "ConflictInMappingEntry";
		break;
	case 724:
		s = "SamePortValuesRequired";
		break;
	case 725:
		s = "OnlyPermanentLeasesSupported";
		break;
	case 726:
		s = "RemoteHostOnlySupportsWildcard";
		break;
	case 727:
		s = "ExternalPortOnlySupportsWildcard";
		break;
	default:
		s = "UnknownError";
		break;
	}
	return s;
}