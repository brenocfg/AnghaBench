#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dvb_ca_private {TYPE_1__* pub; } ;
struct TYPE_4__ {int (* read_attribute_mem ) (TYPE_1__*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int,...) ; 
 int stub1 (TYPE_1__*,int,int) ; 
 int stub2 (TYPE_1__*,int,int) ; 
 int stub3 (TYPE_1__*,int,int) ; 

__attribute__((used)) static int dvb_ca_en50221_read_tuple(struct dvb_ca_private *ca, int slot,
				     int *address, int *tupleType, int *tupleLength, u8 * tuple)
{
	int i;
	int _tupleType;
	int _tupleLength;
	int _address = *address;

	/* grab the next tuple length and type */
	if ((_tupleType = ca->pub->read_attribute_mem(ca->pub, slot, _address)) < 0)
		return _tupleType;
	if (_tupleType == 0xff) {
		dprintk("END OF CHAIN TUPLE type:0x%x\n", _tupleType);
		*address += 2;
		*tupleType = _tupleType;
		*tupleLength = 0;
		return 0;
	}
	if ((_tupleLength = ca->pub->read_attribute_mem(ca->pub, slot, _address + 2)) < 0)
		return _tupleLength;
	_address += 4;

	dprintk("TUPLE type:0x%x length:%i\n", _tupleType, _tupleLength);

	/* read in the whole tuple */
	for (i = 0; i < _tupleLength; i++) {
		tuple[i] = ca->pub->read_attribute_mem(ca->pub, slot, _address + (i * 2));
		dprintk("  0x%02x: 0x%02x %c\n",
			i, tuple[i] & 0xff,
			((tuple[i] > 31) && (tuple[i] < 127)) ? tuple[i] : '.');
	}
	_address += (_tupleLength * 2);

	// success
	*tupleType = _tupleType;
	*tupleLength = _tupleLength;
	*address = _address;
	return 0;
}