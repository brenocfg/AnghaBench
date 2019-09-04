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
typedef  int I_32 ;

/* Variables and functions */
#define  HYPORT_ERROR_FILE_LOCKED 176 
#define  HYPORT_ERROR_SOCKET_ADDRINUSE 175 
#define  HYPORT_ERROR_SOCKET_ADDRNOTAVAIL 174 
#define  HYPORT_ERROR_SOCKET_ALREADYBOUND 173 
#define  HYPORT_ERROR_SOCKET_ARGSINVALID 172 
#define  HYPORT_ERROR_SOCKET_BADAF 171 
#define  HYPORT_ERROR_SOCKET_BADDESC 170 
#define  HYPORT_ERROR_SOCKET_BADPROTO 169 
#define  HYPORT_ERROR_SOCKET_BADSOCKET 168 
#define  HYPORT_ERROR_SOCKET_BADTYPE 167 
#define  HYPORT_ERROR_SOCKET_BOUNDORCONN 166 
#define  HYPORT_ERROR_SOCKET_CONNECTION_REFUSED 165 
#define  HYPORT_ERROR_SOCKET_CONNRESET 164 
#define  HYPORT_ERROR_SOCKET_FDSETALLOCFAIL 163 
#define  HYPORT_ERROR_SOCKET_FDSETFULL 162 
#define  HYPORT_ERROR_SOCKET_FDSET_SIZEBAD 161 
#define  HYPORT_ERROR_SOCKET_HOSTENTALLOCFAIL 160 
#define  HYPORT_ERROR_SOCKET_HOSTNOTFOUND 159 
#define  HYPORT_ERROR_SOCKET_INTERRUPTED 158 
#define  HYPORT_ERROR_SOCKET_INVALIDTIMEOUT 157 
#define  HYPORT_ERROR_SOCKET_IPMREQALLOCFAIL 156 
#define  HYPORT_ERROR_SOCKET_ISCONNECTED 155 
#define  HYPORT_ERROR_SOCKET_LINGERALLOCFAIL 154 
#define  HYPORT_ERROR_SOCKET_MSGSIZE 153 
#define  HYPORT_ERROR_SOCKET_NBWITHLINGER 152 
#define  HYPORT_ERROR_SOCKET_NOBUFFERS 151 
#define  HYPORT_ERROR_SOCKET_NODATA 150 
#define  HYPORT_ERROR_SOCKET_NORECOVERY 149 
#define  HYPORT_ERROR_SOCKET_NOTBOUND 148 
#define  HYPORT_ERROR_SOCKET_NOTCONNECTED 147 
#define  HYPORT_ERROR_SOCKET_NOTINITIALIZED 146 
#define  HYPORT_ERROR_SOCKET_NOTLISTENING 145 
#define  HYPORT_ERROR_SOCKET_NOTSOCK 144 
#define  HYPORT_ERROR_SOCKET_NOTSTREAMSOCK 143 
#define  HYPORT_ERROR_SOCKET_OPNOTSUPP 142 
#define  HYPORT_ERROR_SOCKET_OPTARGSINVALID 141 
#define  HYPORT_ERROR_SOCKET_OPTUNSUPP 140 
#define  HYPORT_ERROR_SOCKET_REMSOCKSHUTDOWN 139 
#define  HYPORT_ERROR_SOCKET_SOCKADDRALLOCFAIL 138 
#define  HYPORT_ERROR_SOCKET_SOCKLEVELINVALID 137 
#define  HYPORT_ERROR_SOCKET_SYSTEMBUSY 136 
#define  HYPORT_ERROR_SOCKET_SYSTEMFULL 135 
#define  HYPORT_ERROR_SOCKET_TIMEOUT 134 
#define  HYPORT_ERROR_SOCKET_TIMEOUTFAILURE 133 
#define  HYPORT_ERROR_SOCKET_TIMEVALALLOCFAIL 132 
#define  HYPORT_ERROR_SOCKET_TIMEVALFULL 131 
#define  HYPORT_ERROR_SOCKET_UNKNOWNFLAG 130 
#define  HYPORT_ERROR_SOCKET_UNKNOWNSOCKET 129 
#define  HYPORT_ERROR_SOCKET_WOULDBLOCK 128 
 scalar_t__ hysock_error_message () ; 

char* netLookupErrorString (I_32 anErrorNum)
{
    switch (anErrorNum)
    {
        case HYPORT_ERROR_SOCKET_BADSOCKET:
            return "Bad socket";
        case HYPORT_ERROR_SOCKET_NOTINITIALIZED:
            return "Socket library uninitialized";
        case HYPORT_ERROR_SOCKET_BADAF:
            return "Bad address family";
        case HYPORT_ERROR_SOCKET_BADPROTO:
            return "Bad protocol";
        case HYPORT_ERROR_SOCKET_BADTYPE:
            return "Bad type";
        case HYPORT_ERROR_SOCKET_SYSTEMBUSY:
            return "System busy handling requests";
        case HYPORT_ERROR_SOCKET_SYSTEMFULL:
            return "Too many sockets allocated";
        case HYPORT_ERROR_SOCKET_NOTCONNECTED:
            return "Socket is not connected";
        case HYPORT_ERROR_SOCKET_INTERRUPTED:
            return "The call was cancelled";
        case HYPORT_ERROR_SOCKET_TIMEOUT:
            return "The operation timed out";
        case HYPORT_ERROR_SOCKET_CONNRESET:
            return "The connection was reset";
        case HYPORT_ERROR_SOCKET_WOULDBLOCK:
            return "The socket is marked as nonblocking operation would block";
        case HYPORT_ERROR_SOCKET_ADDRNOTAVAIL:
            return "The address is not available";
        case HYPORT_ERROR_SOCKET_ADDRINUSE:
            return "The address is already in use";
        case HYPORT_ERROR_SOCKET_NOTBOUND:
            return "The socket is not bound";
        case HYPORT_ERROR_SOCKET_UNKNOWNSOCKET:
            return "Resolution of the FileDescriptor to socket failed";
        case HYPORT_ERROR_SOCKET_INVALIDTIMEOUT:
            return "The specified timeout is invalid";
        case HYPORT_ERROR_SOCKET_FDSETFULL:
            return "Unable to create an FDSET";
        case HYPORT_ERROR_SOCKET_TIMEVALFULL:
            return "Unable to create a TIMEVAL";
        case HYPORT_ERROR_SOCKET_REMSOCKSHUTDOWN:
            return "The remote socket has shutdown gracefully";
        case HYPORT_ERROR_SOCKET_NOTLISTENING:
            return "Listen() was not invoked prior to accept()";
        case HYPORT_ERROR_SOCKET_NOTSTREAMSOCK:
            return "The socket does not support connection-oriented service";
        case HYPORT_ERROR_SOCKET_ALREADYBOUND:
            return "The socket is already bound to an address";
        case HYPORT_ERROR_SOCKET_NBWITHLINGER:
            return "The socket is marked non-blocking & SO_LINGER is non-zero";
        case HYPORT_ERROR_SOCKET_ISCONNECTED:
            return "The socket is already connected";
        case HYPORT_ERROR_SOCKET_NOBUFFERS:
            return "No buffer space is available";
        case HYPORT_ERROR_SOCKET_HOSTNOTFOUND:
            return "Authoritative Answer Host not found";
        case HYPORT_ERROR_SOCKET_NODATA:
            return "Valid name, no data record of requested type";
        case HYPORT_ERROR_SOCKET_BOUNDORCONN:
            return "The socket has not been bound or is already connected";
        case HYPORT_ERROR_SOCKET_OPNOTSUPP:
            return "The socket does not support the operation";
        case HYPORT_ERROR_SOCKET_OPTUNSUPP:
            return "The socket option is not supported";
        case HYPORT_ERROR_SOCKET_OPTARGSINVALID:
            return "The socket option arguments are invalid";
        case HYPORT_ERROR_SOCKET_SOCKLEVELINVALID:
            return "The socket level is invalid";
        case HYPORT_ERROR_SOCKET_TIMEOUTFAILURE:
            return "The timeout operation failed";
        case HYPORT_ERROR_SOCKET_SOCKADDRALLOCFAIL:
            return "Failed to allocate address structure";
        case HYPORT_ERROR_SOCKET_FDSET_SIZEBAD:
            return "The calculated maximum size of the file descriptor set is bad";
        case HYPORT_ERROR_SOCKET_UNKNOWNFLAG:
            return "The flag is unknown";
        case HYPORT_ERROR_SOCKET_MSGSIZE:
            return "The datagram was too big to fit the specified buffer, so truncated";
        case HYPORT_ERROR_SOCKET_NORECOVERY:
            return "The operation failed with no recovery possible";
        case HYPORT_ERROR_SOCKET_ARGSINVALID:
            return "The arguments are invalid";
        case HYPORT_ERROR_SOCKET_BADDESC:
            return "The socket argument is not a valid file descriptor";
        case HYPORT_ERROR_SOCKET_NOTSOCK:
            return "The socket argument is not a socket";
        case HYPORT_ERROR_SOCKET_HOSTENTALLOCFAIL:
            return "Unable to allocate the hostent structure";
        case HYPORT_ERROR_SOCKET_TIMEVALALLOCFAIL:
            return "Unable to allocate the timeval structure";
        case HYPORT_ERROR_SOCKET_LINGERALLOCFAIL:
            return "Unable to allocate the linger structure";
        case HYPORT_ERROR_SOCKET_IPMREQALLOCFAIL:
            return "Unable to allocate the ipmreq structure";
        case HYPORT_ERROR_SOCKET_FDSETALLOCFAIL:
            return "Unable to allocate the fdset structure";
        case HYPORT_ERROR_SOCKET_CONNECTION_REFUSED:
            return "Connection refused";
        case HYPORT_ERROR_FILE_LOCKED:
            return "File has been locked by another process";
            
        default:
            return (char *) hysock_error_message ();
    }
}