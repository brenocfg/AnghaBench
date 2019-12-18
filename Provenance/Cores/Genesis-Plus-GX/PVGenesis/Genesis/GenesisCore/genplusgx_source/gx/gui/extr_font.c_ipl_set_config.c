__attribute__((used)) static void ipl_set_config(unsigned char c)
{
  volatile unsigned long* exi = (volatile unsigned long*)0xCC006800;
  unsigned long val,addr;
  addr=0xc0000000;
  val = c << 24;
  exi[0] = ((((exi[0]) & 0x405) | 256) | 48);     //select IPL
  //write addr of IPL
  exi[0 * 5 + 4] = addr;
  exi[0 * 5 + 3] = ((4 - 1) << 4) | (1 << 2) | 1;
  while (exi[0 * 5 + 3] & 1);
  //write the ipl we want to send
  exi[0 * 5 + 4] = val;
  exi[0 * 5 + 3] = ((4 - 1) << 4) | (1 << 2) | 1;
  while (exi[0 * 5 + 3] & 1);
  exi[0] &= 0x405;        //deselect IPL
}