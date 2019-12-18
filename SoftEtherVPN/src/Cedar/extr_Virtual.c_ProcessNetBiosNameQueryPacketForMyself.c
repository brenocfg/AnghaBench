#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  my_pcname ;
struct TYPE_12__ {int /*<<< orphan*/  HostIP; } ;
typedef  TYPE_1__ VH ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  int UCHAR ;
struct TYPE_13__ {int Size; int /*<<< orphan*/  Buf; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 scalar_t__ Cmp (int*,int*,int) ; 
 int /*<<< orphan*/  EncodeNetBiosName (int*,char*) ; 
 int Endian16 (int) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsIPPrivate (int /*<<< orphan*/ *) ; 
 int IsLocalHostIP4 (int /*<<< orphan*/ *) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 TYPE_2__* NewBuf () ; 
 TYPE_2__* NewBufFromMemory (void*,scalar_t__) ; 
 int ReadBuf (TYPE_2__*,int*,int) ; 
 int /*<<< orphan*/  SendUdp (TYPE_1__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 unsigned long long Tick64 () ; 
 int /*<<< orphan*/  WHERE ; 
 int /*<<< orphan*/  WriteBuf (TYPE_2__*,...) ; 
 int /*<<< orphan*/  WriteBufBuf (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

bool ProcessNetBiosNameQueryPacketForMyself(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, void *data, UINT size)
{
	BUF *rb;
	USHORT tran_id;
	USHORT flags;
	USHORT num_query;
	USHORT zero1, zero2, zero3;
	UCHAR name_size;
	UCHAR encoded_name[32];
	UCHAR node_type;
	USHORT type, classid;
	UCHAR my_pc_encoded_name[32];
	bool ret = false;
	// Validate arguments
	if (v == NULL || data == NULL)
	{
		return false;
	}

	rb = NewBufFromMemory(data, size);

	ReadBuf(rb, &tran_id, sizeof(USHORT));

	ReadBuf(rb, &flags, sizeof(USHORT));
	flags = Endian16(flags);

	ReadBuf(rb, &num_query, sizeof(USHORT));
	num_query = Endian16(num_query);

	ReadBuf(rb, &zero1, sizeof(USHORT));
	ReadBuf(rb, &zero2, sizeof(USHORT));
	ReadBuf(rb, &zero3, sizeof(USHORT));

	ReadBuf(rb, &name_size, 1);

	ReadBuf(rb, encoded_name, 32);

	ReadBuf(rb, &node_type, 1);

	ReadBuf(rb, &type, sizeof(USHORT));
	type = Endian16(type);

	if (ReadBuf(rb, &classid, sizeof(USHORT)) == sizeof(USHORT))
	{
		classid = Endian16(classid);

		if (((flags >> 11) & 0x0F) == 0 &&
			num_query == 1 && name_size == 0x20 &&
			zero1 == 0 && zero2 == 0 && zero3 == 0 && node_type == 0 && type == 0x0020 && classid == 0x0001)
		{
			char my_pcname[MAX_SIZE];

			// Get the encoded name of this PC
			Zero(my_pcname, sizeof(my_pcname));
			GetMachineHostName(my_pcname, sizeof(my_pcname));

			EncodeNetBiosName(my_pc_encoded_name, my_pcname);

			if (Cmp(my_pc_encoded_name, encoded_name, 30) == 0)
			{
				// Assemble the response packet since the name resolution packet which targets this PC name received
				BUF *sb = NewBuf();
				USHORT us;
				UINT ui;
				LIST *ip_list;
				BUF *ip_list_buf;
				bool found = false;

				WriteBuf(sb, &tran_id, sizeof(USHORT));

				flags = Endian16(0x8500);
				WriteBuf(sb, &flags, sizeof(USHORT));

				num_query = 0;
				WriteBuf(sb, &num_query, sizeof(USHORT));

				us = Endian16(1);
				WriteBuf(sb, &us, sizeof(USHORT));

				us = 0;
				WriteBuf(sb, &us, sizeof(USHORT));
				WriteBuf(sb, &us, sizeof(USHORT));

				name_size = 0x20;
				WriteBuf(sb, &name_size, 1);

				WriteBuf(sb, encoded_name, 32);

				node_type = 0;
				WriteBuf(sb, &node_type, 1);

				type = Endian16(type);
				classid = Endian16(classid);

				WriteBuf(sb, &type, sizeof(USHORT));
				WriteBuf(sb, &classid, sizeof(USHORT));

				ui = Endian32((UINT)(Tick64() / 1000ULL));
				WriteBuf(sb, &ui, sizeof(UINT));

				ip_list_buf = NewBuf();

				ip_list = GetHostIPAddressList();
				if (ip_list != NULL)
				{
					UINT i;

					// Return only private IP if there is a private IP
					for (i = 0;i < LIST_NUM(ip_list);i++)
					{
						IP *ip = LIST_DATA(ip_list, i);

						if (IsIP4(ip) && IsLocalHostIP4(ip) == false && IsZeroIp(ip) == false)
						{
							if (IsIPPrivate(ip))
							{
								USHORT flags = Endian16(0x4000);
								UINT ip_uint = IPToUINT(ip);

								WriteBuf(ip_list_buf, &flags, sizeof(USHORT));
								WriteBuf(ip_list_buf, &ip_uint, sizeof(UINT));

								found = true;
							}
						}
					}

					if (found == false)
					{
						// Return all IP if no private IP are found
						for (i = 0;i < LIST_NUM(ip_list);i++)
						{
							IP *ip = LIST_DATA(ip_list, i);

							if (IsIP4(ip) && IsLocalHostIP4(ip) == false && IsZeroIp(ip) == false)
							{
								USHORT flags = Endian16(0x4000);
								UINT ip_uint = IPToUINT(ip);

								WriteBuf(ip_list_buf, &flags, sizeof(USHORT));
								WriteBuf(ip_list_buf, &ip_uint, sizeof(UINT));

								found = true;
							}
						}
					}

					FreeHostIPAddressList(ip_list);
				}

				us = Endian16(ip_list_buf->Size);
				WriteBuf(sb, &us, sizeof(USHORT));

				WriteBufBuf(sb, ip_list_buf);

				SendUdp(v, src_ip, src_port, v->HostIP, dest_port, sb->Buf, sb->Size);

				FreeBuf(ip_list_buf);

				FreeBuf(sb);

				WHERE;
			}
		}
	}

	FreeBuf(rb);

	return ret;
}