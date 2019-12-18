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
typedef  int apr_status_t ;

/* Variables and functions */
#define  APR_ANONYMOUS 172 
#define  APR_BADARG 171 
#define  APR_BADCH 170 
#define  APR_CHILD_DONE 169 
#define  APR_CHILD_NOTDONE 168 
#define  APR_DETACH 167 
#define  APR_EABOVEROOT 166 
#define  APR_EABSOLUTE 165 
#define  APR_EBADDATE 164 
#define  APR_EBADIP 163 
#define  APR_EBADMASK 162 
#define  APR_EBADPATH 161 
#define  APR_EBUSY 160 
#define  APR_EDSOOPEN 159 
#define  APR_EGENERAL 158 
#define  APR_EINCOMPLETE 157 
#define  APR_EINIT 156 
#define  APR_EINVALSOCK 155 
#define  APR_EMISMATCH 154 
#define  APR_ENODIR 153 
#define  APR_ENOLOCK 152 
#define  APR_ENOPOLL 151 
#define  APR_ENOPOOL 150 
#define  APR_ENOPROC 149 
#define  APR_ENOSHMAVAIL 148 
#define  APR_ENOSOCKET 147 
#define  APR_ENOSTAT 146 
#define  APR_ENOTENOUGHENTROPY 145 
#define  APR_ENOTHDKEY 144 
#define  APR_ENOTHREAD 143 
#define  APR_ENOTIME 142 
#define  APR_ENOTIMPL 141 
#define  APR_EOF 140 
#define  APR_EPATHWILD 139 
#define  APR_EPROC_UNKNOWN 138 
#define  APR_ERELATIVE 137 
#define  APR_ESYMNOTFOUND 136 
#define  APR_FILEBASED 135 
#define  APR_INCHILD 134 
#define  APR_INCOMPLETE 133 
#define  APR_INPARENT 132 
#define  APR_KEYBASED 131 
#define  APR_NOTDETACH 130 
#define  APR_NOTFOUND 129 
#define  APR_TIMEUP 128 
 char* dlerror () ; 

__attribute__((used)) static char *apr_error_string(apr_status_t statcode)
{
    switch (statcode) {
    case APR_ENOSTAT:
        return "Could not perform a stat on the file.";
    case APR_ENOPOOL:
        return "A new pool could not be created.";
    case APR_EBADDATE:
        return "An invalid date has been provided";
    case APR_EINVALSOCK:
        return "An invalid socket was returned";
    case APR_ENOPROC:
        return "No process was provided and one was required.";
    case APR_ENOTIME:
        return "No time was provided and one was required.";
    case APR_ENODIR:
        return "No directory was provided and one was required.";
    case APR_ENOLOCK:
        return "No lock was provided and one was required.";
    case APR_ENOPOLL:
        return "No poll structure was provided and one was required.";
    case APR_ENOSOCKET:
        return "No socket was provided and one was required.";
    case APR_ENOTHREAD:
        return "No thread was provided and one was required.";
    case APR_ENOTHDKEY:
        return "No thread key structure was provided and one was required.";
    case APR_ENOSHMAVAIL:
        return "No shared memory is currently available";
    case APR_EDSOOPEN:
#if APR_HAS_DSO && defined(HAVE_LIBDL)
        return dlerror();
#else
        return "DSO load failed";
#endif /* HAVE_LIBDL */
    case APR_EBADIP:
        return "The specified IP address is invalid.";
    case APR_EBADMASK:
        return "The specified network mask is invalid.";
    case APR_ESYMNOTFOUND:
        return "Could not find the requested symbol.";
    case APR_ENOTENOUGHENTROPY:
        return "Not enough entropy to continue.";
    case APR_INCHILD:
        return
	    "Your code just forked, and you are currently executing in the "
	    "child process";
    case APR_INPARENT:
        return
	    "Your code just forked, and you are currently executing in the "
	    "parent process";
    case APR_DETACH:
        return "The specified thread is detached";
    case APR_NOTDETACH:
        return "The specified thread is not detached";
    case APR_CHILD_DONE:
        return "The specified child process is done executing";
    case APR_CHILD_NOTDONE:
        return "The specified child process is not done executing";
    case APR_TIMEUP:
        return "The timeout specified has expired";
    case APR_INCOMPLETE:
        return "Partial results are valid but processing is incomplete";
    case APR_BADCH:
        return "Bad character specified on command line";
    case APR_BADARG:
        return "Missing parameter for the specified command line option";
    case APR_EOF:
        return "End of file found";
    case APR_NOTFOUND:
        return "Could not find specified socket in poll list.";
    case APR_ANONYMOUS:
        return "Shared memory is implemented anonymously";
    case APR_FILEBASED:
        return "Shared memory is implemented using files";
    case APR_KEYBASED:
        return "Shared memory is implemented using a key system";
    case APR_EINIT:
        return
	    "There is no error, this value signifies an initialized "
	    "error code";
    case APR_ENOTIMPL:
        return "This function has not been implemented on this platform";
    case APR_EMISMATCH:
        return "passwords do not match";
    case APR_EABSOLUTE:
        return "The given path is absolute";
    case APR_ERELATIVE:
        return "The given path is relative";
    case APR_EINCOMPLETE:
        return "The given path is incomplete";
    case APR_EABOVEROOT:
        return "The given path was above the root path";
    case APR_EBADPATH:
        return "The given path is misformatted or contained invalid characters";
    case APR_EPATHWILD:
        return "The given path contained wildcard characters";
    case APR_EBUSY:
        return "The given lock was busy.";
    case APR_EPROC_UNKNOWN:
        return "The process is not recognized.";
    case APR_EGENERAL:
        return "Internal error (specific information not available)";
    default:
        return "Error string not specified yet";
    }
}