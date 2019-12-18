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
struct tape_request {char* cpdata; scalar_t__ cpaddr; int /*<<< orphan*/  op; } ;
struct tape_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int /*<<< orphan*/  ENOSYS ; 
 struct tape_request* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct tape_request*) ; 
 int /*<<< orphan*/  MODE_SET_CB ; 
 int /*<<< orphan*/  TO_CRYPT_ON ; 
 int /*<<< orphan*/  crypt_supported (struct tape_device*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 struct tape_request* tape_alloc_request (int,int) ; 
 int /*<<< orphan*/  tape_ccw_cc (scalar_t__,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  tape_ccw_end (scalar_t__,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static struct tape_request *__tape_3592_enable_crypt(struct tape_device *device)
{
	struct tape_request *request;
	char *data;

	DBF_EVENT(6, "tape_3592_enable_crypt\n");
	if (!crypt_supported(device))
		return ERR_PTR(-ENOSYS);
	request = tape_alloc_request(2, 72);
	if (IS_ERR(request))
		return request;
	data = request->cpdata;
	memset(data,0,72);

	data[0]       = 0x05;
	data[36 + 0]  = 0x03;
	data[36 + 1]  = 0x03;
	data[36 + 4]  = 0x40;
	data[36 + 6]  = 0x01;
	data[36 + 14] = 0x2f;
	data[36 + 18] = 0xc3;
	data[36 + 35] = 0x72;
	request->op = TO_CRYPT_ON;
	tape_ccw_cc(request->cpaddr, MODE_SET_CB, 36, data);
	tape_ccw_end(request->cpaddr + 1, MODE_SET_CB, 36, data + 36);
	return request;
}