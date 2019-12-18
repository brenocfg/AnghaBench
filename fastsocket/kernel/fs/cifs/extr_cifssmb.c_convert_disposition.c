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
typedef  int __u16 ;

/* Variables and functions */
#define  FILE_CREATE 133 
#define  FILE_OPEN 132 
#define  FILE_OPEN_IF 131 
#define  FILE_OVERWRITE 130 
#define  FILE_OVERWRITE_IF 129 
#define  FILE_SUPERSEDE 128 
 int SMBOPEN_OAPPEND ; 
 int SMBOPEN_OCREATE ; 
 int SMBOPEN_OTRUNC ; 
 int /*<<< orphan*/  cFYI (int,char*,int) ; 

__attribute__((used)) static __u16 convert_disposition(int disposition)
{
	__u16 ofun = 0;

	switch (disposition) {
		case FILE_SUPERSEDE:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OTRUNC;
			break;
		case FILE_OPEN:
			ofun = SMBOPEN_OAPPEND;
			break;
		case FILE_CREATE:
			ofun = SMBOPEN_OCREATE;
			break;
		case FILE_OPEN_IF:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OAPPEND;
			break;
		case FILE_OVERWRITE:
			ofun = SMBOPEN_OTRUNC;
			break;
		case FILE_OVERWRITE_IF:
			ofun = SMBOPEN_OCREATE | SMBOPEN_OTRUNC;
			break;
		default:
			cFYI(1, "unknown disposition %d", disposition);
			ofun =  SMBOPEN_OAPPEND; /* regular open */
	}
	return ofun;
}